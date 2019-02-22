#include "generaltraverser.hh"

static void ScanGeneral(const vector<char> &bytes, int *codes, int *empties) {
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    
    *codes = 0;
    *empties = 0;
    
    bool hasCode = false;
    for (; ptr < end; ++ptr) {
        if (*ptr == '\n') {
            hasCode ? (*codes += 1) : (*empties += 1);
            hasCode = false;
        } else if (*ptr != ' ' && *ptr != '\t') {
            hasCode = true;
        }
    }
    if (hasCode) {
        *codes += 1;
    } else {
        *empties += 1;
    }
}

// ---- ---- ---- ---- ---- ---- - "0123456789_123456789_1234"
static const char sDefaultTag [] = "[                       ]";
static const char sTitleFirst [] = "[ sum   code     empty  ]";
static const char sTitleSecond[] = "[---- -------- ---------]";
static const char sOpenFailed [] = "[  the File Open Error  ]";
static const char sFILENotUTF8[] = "[  the File is not UTF8 ]";
static const char sPrintFormat[] = "[%4d %4d/%2d%% %4d/%2d%% ]";

static void PrintResult(int files, int codes, int empties) {
    
    int total  = codes + empties;
    int codeP  = (codes   == total) ? 99 : (codes   * 100 / total);
    int emptyP = (empties == total) ? 99 : (empties * 100 / total);
    
    I("file count: %s\n", Traverser::ts(files));
    I("total line: %s\n", Traverser::ts(total));
    I("code  line: %s(%2d%%)\n", Traverser::ts(codes  ), codeP );
    I("empty line: %s(%2d%%)\n", Traverser::ts(empties), emptyP);
}

void GeneralTraverser::onStart(vector<string> *outTypes, string *outDefaultTag) {
    
    *outTypes = {".java", ".h", ".hh", ".m", ".mm", ".cpp", ".cs", ".lua"};
    *outDefaultTag = sDefaultTag;
    
    _tFiles = 0;
    _tCodes = 0;
    _tEmpties = 0;
    
    I("%s\n", sTitleFirst );
    I("%s\n", sTitleSecond);
}

void GeneralTraverser::onBeginTask() {
    
    _aFiles = 0;
    _aCodes = 0;
    _aEmpties = 0;
}

void GeneralTraverser::onHandleFile(const string &file, string *outTag) {
    outTag->append(24, ' ');
    
    vector<char> content;
    if (CQReadFile(file, &content) != CQFileError::None) {
        sprintf((char *)outTag->data(), "%s", sOpenFailed);
        return;
    }
    
    vector<char> utf8;
    if (!CQUTF8Check(content, nullptr, &utf8)) {
        sprintf((char *)outTag->data(), "%s", sFILENotUTF8);
        return;
    }
    
    //this is one
    int codes = 0;
    int empties = 0;
    ScanGeneral(utf8, &codes, &empties);
    
    int total  = codes + empties;
    int codeP  = (codes   == total) ? 99 : (codes   * 100 / total);
    int emptyP = (empties == total) ? 99 : (empties * 100 / total);
    sprintf((char *)outTag->data(), sPrintFormat, total, codes, codeP, empties, emptyP);
    
    //sum
    _aFiles += 1;
    _aCodes += codes;
    _aEmpties += empties;
    
    _tFiles += 1;
    _tCodes += codes;
    _tEmpties += empties;
}

void GeneralTraverser::onEndTask() {
    PrintResult(_aFiles, _aCodes, _aEmpties);
}

void GeneralTraverser::onStop() {
    I("total:\n\n");
    PrintResult(_tFiles, _tCodes, _tEmpties);
}
