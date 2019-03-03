#include "ccgeneraltraverser.hh"

static void ScanSource(const vector<char> &bytes, int *codeLine, int *emptyLine) {
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    
    *codeLine = 0;
    *emptyLine = 0;
    
    bool hasCode = false;
    for (; ptr < end; ++ptr) {
        if (*ptr == '\n') {
            
            if (hasCode) {
                *codeLine += 1;
            } else {
                *emptyLine += 1;
            }
            hasCode = false;
            
        } else if (*ptr != ' ' && *ptr != '\t') {
            
            hasCode = true;
        }
    }
    if (hasCode) {
        *codeLine += 1;
    } else {
        *emptyLine += 1;
    }
}

static const char sTitleFirst [] = "|total|  code  |  empty  |";
static const char sTitleSecond[] = "|-----|--------|---------|";
static const char sEmptyTitle [] = "[                        ]";
static const char sOpenFailed [] = "[  the File Open Error   ]";
static const char sNotUTF8    [] = "[  the File is not UTF8  ]";
static const char sPrintFormat[] = "[%5d %4d/%2d%% %4d/%2d%% ] %*s%s";

static void PrintDetail(int fileCount, int codeLine, int emptyLine) {
    
    int totalLine  = codeLine + emptyLine;
    
    space_line(1).print("file count: %s", CCFormatted(fileCount));
    start_newline.print("total line: %s", CCFormatted(totalLine));
    start_newline.print("code  line: %s(%2d%%)", CCFormatted(codeLine ), CCPercent(codeLine , totalLine));
    start_newline.print("empty line: %s(%2d%%)", CCFormatted(emptyLine), CCPercent(emptyLine, totalLine));
}

struct CCGeneralGlobal : CCGlobal {
    int fileCount = 0;
    int codeLine  = 0;
    int emptyLine = 0;
};

struct CCGeneralStage : CCStage {
    int fileCount  = 0;
    int codeLine   = 0;
    int emptyLine  = 0;
    int printCount = 0;
};

void CCGeneralTraverser::onBegin(CCData *data) {
    data->global = new CCGeneralGlobal;
}

void CCGeneralTraverser::onBeginStage(CCData *data) {
    data->stage = new CCGeneralStage;
}

void CCGeneralTraverser::onHandleDirectory(CCData *data, const string &name, int indent) {
    start_newline.print("%s %*s%s/", sEmptyTitle, indent * 2, "", name.c_str());
}

void CCGeneralTraverser::onHandleFile(CCData *data, const string &name, int indent) {
    
    static const vector<string> types = {".java", ".h", ".hh", ".m", ".mm", ".cpp", ".cs", ".lua"};
    vector<char> content;
    switch (CCReadUTF8File(name, types, &content)) {
        case CQErrorOpenFailed: start_newline.print("%s %*s%s", sOpenFailed, indent * 2, "", name.c_str()); return;
        case CQErrorNotUTF8   : start_newline.print("%s %*s%s", sNotUTF8   , indent * 2, "", name.c_str()); return;
        default:;
    }
    
    int codeLine = 0;
    int emptyLine = 0;
    ScanSource(content, &codeLine, &emptyLine);
    
    auto global = (CCGeneralGlobal *)data->global;
    auto stage  = (CCGeneralStage  *)data->stage ;
    
    if (stage->printCount % 10 == 0) {
        start_newline.print("%s", sTitleFirst);
        start_newline.print("%s", sTitleSecond);
    }
    start_newline.print(sPrintFormat,
        codeLine + emptyLine,
        codeLine , CCPercent(codeLine , codeLine + emptyLine),
        emptyLine, CCPercent(emptyLine, codeLine + emptyLine),
        indent * 2, "",
        name.c_str());
    
    global->fileCount += 1;
    global->codeLine  += codeLine ;
    global->emptyLine += emptyLine;

    stage->fileCount  += 1;
    stage->codeLine   += codeLine;
    stage->emptyLine  += emptyLine;
    stage->printCount += 1;
}

void CCGeneralTraverser::onEndStage(CCData *data) {
    auto stage = (CCGeneralStage *)data->stage;
    
    PrintDetail(stage->fileCount, stage->codeLine, stage->emptyLine);
}

void CCGeneralTraverser::onEnd(CCData *data) {
    auto global = (CCGeneralGlobal *)data->global;
    
    space_line(1).print("SUM:");
    PrintDetail(global->fileCount, global->codeLine, global->emptyLine);
    space_line(1);
}
