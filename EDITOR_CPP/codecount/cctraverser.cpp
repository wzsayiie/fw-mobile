#include "cctraverser.hh"

static bool IsSupportedFile(const string &name, const vector<string> &suffixes) {
    for (const string &it : suffixes) {
        if (name.has_suffix(it)) {
            return true;
        }
    }
    return false;
}

static int GetTotalLine(CCStatisticsMask options, const CCStatisticsData &data) {
    int totalLine = 0;
    
    if (options & CCStatisticsMaskCodeLine   ) { totalLine += data.codeLine   ; }
    if (options & CCStatisticsMaskCodeAndCmnt) { totalLine += data.codeAndCmnt; }
    if (options & CCStatisticsMaskCommentLine) { totalLine += data.commentLine; }
    if (options & CCStatisticsMaskEmptyLine  ) { totalLine += data.emptyLine  ; }
    
    return totalLine;
}

static void PrintNameComponent(const string &name, const char *tail, int indent) {
    if (!name.empty()) {
        continue_last.print(" %*s%s%s", indent * 2, "", name.c_str(), tail);
    }
}

const int nHeader0 = 1;
const int nHeader1 = 2;
const int nEmpty   = 3;
const int nReadErr = 4;
const int nNotUTF8 = 5;

static void PrintLine(CCStatisticsMask m, int n, const string &name, const char *tail, int indent) {
    
    if /**/ (n == nHeader0) { start_newline.print("| sum"); }
    else if (n == nHeader1) { start_newline.print("|----"); }
    else if (n == nEmpty  ) { start_newline.print("[    "); }
    else if (n == nReadErr) { start_newline.print("[    "); }
    else if (n == nNotUTF8) { start_newline.print("[    "); }
    
    if /**/ (n == nHeader0 && (m & CCStatisticsMaskCodeLine   )) { continue_last.print("|  code  "); }
    else if (n == nHeader1 && (m & CCStatisticsMaskCodeLine   )) { continue_last.print("|--------"); }
    else if (n == nEmpty   && (m & CCStatisticsMaskCodeLine   )) { continue_last.print("         "); }
    else if (n == nReadErr && (m & CCStatisticsMaskCodeLine   )) { continue_last.print(" READ ERR"); }
    else if (n == nNotUTF8 && (m & CCStatisticsMaskCodeLine   )) { continue_last.print(" NOT UTF8"); }
    
    if /**/ (n == nHeader0 && (m & CCStatisticsMaskCodeAndCmnt)) { continue_last.print("|cod&cmnt"); }
    else if (n == nHeader1 && (m & CCStatisticsMaskCodeAndCmnt)) { continue_last.print("|--------"); }
    else if (n == nEmpty   && (m & CCStatisticsMaskCodeAndCmnt)) { continue_last.print("         "); }
    else if (n == nReadErr && (m & CCStatisticsMaskCodeAndCmnt)) { continue_last.print("         "); }
    else if (n == nNotUTF8 && (m & CCStatisticsMaskCodeAndCmnt)) { continue_last.print("         "); }
    
    if /**/ (n == nHeader0 && (m & CCStatisticsMaskCommentLine)) { continue_last.print("| comment"); }
    else if (n == nHeader1 && (m & CCStatisticsMaskCommentLine)) { continue_last.print("|--------"); }
    else if (n == nEmpty   && (m & CCStatisticsMaskCommentLine)) { continue_last.print("         "); }
    else if (n == nReadErr && (m & CCStatisticsMaskCommentLine)) { continue_last.print("         "); }
    else if (n == nNotUTF8 && (m & CCStatisticsMaskCommentLine)) { continue_last.print("         "); }
    
    if /**/ (n == nHeader0 && (m & CCStatisticsMaskEmptyLine  )) { continue_last.print("|  empty "); }
    else if (n == nHeader1 && (m & CCStatisticsMaskEmptyLine  )) { continue_last.print("|--------"); }
    else if (n == nEmpty   && (m & CCStatisticsMaskEmptyLine  )) { continue_last.print("         "); }
    else if (n == nReadErr && (m & CCStatisticsMaskEmptyLine  )) { continue_last.print("         "); }
    else if (n == nNotUTF8 && (m & CCStatisticsMaskEmptyLine  )) { continue_last.print("         "); }
    
    if /**/ (n == nHeader0) { continue_last.print(" |"); }
    else if (n == nHeader1) { continue_last.print("-|"); }
    else if (n == nEmpty  ) { continue_last.print(" ]"); }
    else if (n == nReadErr) { continue_last.print(" ]"); }
    else if (n == nNotUTF8) { continue_last.print(" ]"); }
    
    PrintNameComponent(name, tail, indent);
}

static void PrintDataItem(int part, int total) {
    
    int centage = 0;
    if (total != 0) {
        centage = part * 100 / total;
        centage = centage <= 99 ? centage : 99;
    } else {
        centage = 99;
    }
    
    continue_last.print(" %4d/%02d%%", part, centage);
}

static void PrintDataLine(CCStatisticsMask m, const CCStatisticsData &d, const string &name, const char *tail, int indent) {
    int totalLine = GetTotalLine(m, d);
    start_newline.print("[%4d", totalLine);
    
    if (m & CCStatisticsMaskCodeLine   ) { PrintDataItem(d.codeLine   , totalLine); }
    if (m & CCStatisticsMaskCodeAndCmnt) { PrintDataItem(d.codeAndCmnt, totalLine); }
    if (m & CCStatisticsMaskCommentLine) { PrintDataItem(d.commentLine, totalLine); }
    if (m & CCStatisticsMaskEmptyLine  ) { PrintDataItem(d.emptyLine  , totalLine); }
    
    continue_last.print(" ]");
    
    PrintNameComponent(name, tail, indent);
}

static void PrintSummaryItem(const char *title, int part, int total) {
    
    if (part >= 1000) { start_newline.print("%s:%4d,%03d", title, part / 1000, part % 1000); }
    else /* --- -- */ { start_newline.print("%s:%8d"     , title, part); }
    
    if (0 <= part && part < total) {
        continue_last.print(" (%2d%%)", part * 100 / total);
    }
}

static void PrintSummary(CCStatisticsMask m, int files, const CCStatisticsData &d) {
    int totalLine = GetTotalLine(m, d);
    
    space_line(1);
    /* ---- ---- ---- ---- ---- ---- -- */ PrintSummaryItem("file count  ", files, 0);
    /* ---- ---- ---- ---- ---- ---- -- */ PrintSummaryItem("total line  ", totalLine, 0);
    if (m & CCStatisticsMaskCodeLine   ) { PrintSummaryItem("code line   ", d.codeLine   , totalLine); }
    if (m & CCStatisticsMaskCodeAndCmnt) { PrintSummaryItem("code&comment", d.codeAndCmnt, totalLine); }
    if (m & CCStatisticsMaskCommentLine) { PrintSummaryItem("comment line", d.commentLine, totalLine); }
    if (m & CCStatisticsMaskEmptyLine  ) { PrintSummaryItem("empty line  ", d.emptyLine  , totalLine); }
}

static const CCStatisticsData CCStatisticsDataZero = {0, 0, 0, 0};

static void operator+=(CCStatisticsData &out, const CCStatisticsData &append) {
    out.codeLine    += append.codeLine   ;
    out.codeAndCmnt += append.codeAndCmnt;
    out.commentLine += append.commentLine;
    out.emptyLine   += append.emptyLine  ;
}

void CCTraverser::count(const vector<string> &paths) {
    
    _supportedFiles.clear();
    _supportedOptions = 0;
    _globalData = CCStatisticsDataZero;
    _globalFiles = 0;
    onGetSupportedFiles(&_supportedFiles);
    onGetSupportedOptions(&_supportedOptions);
    
    for (const string &it : paths) {
        space_line(1).print("@ %s:", it.c_str());
        space_line(1);
        
        _stageData = CCStatisticsDataZero;
        _stageFiles = 0;
        CQTraverse(it, this);
        _globalData += _stageData;
        _globalFiles += _stageFiles;
        
        PrintSummary(_supportedOptions, _stageFiles, _stageData);
    }
    
    if (paths.size() > 1) {
        space_line(1).print("total:");
        PrintSummary(_supportedOptions, _globalFiles, _globalData);
    }
}

void CCTraverser::traverserGetDirectory(const string &name, int indent) {
    PrintLine(_supportedOptions, nEmpty, name, "/", indent);
}

void CCTraverser::traverserGetFile(const string &name, int indent) {
    if (!IsSupportedFile(name, _supportedFiles)) {
        return;
    }
    
    if (_stageFiles % 10 == 0) {
        PrintLine(_supportedOptions, nHeader0, "", "", 0);
        PrintLine(_supportedOptions, nHeader1, "", "", 0);
    }
    
    vector<char> bytes;
    if (!CQReadFile(name, &bytes)) {
        PrintLine(_supportedOptions, nReadErr, name, "", indent);
        return;
    }
    vector<char> utf8;
    if (!CQUTF8Check(bytes, nullptr, &utf8)) {
        PrintLine(_supportedOptions, nNotUTF8, name, "", indent);
        return;
    }
    CCStatisticsData data;
    onHandleFile(utf8, &data);
    PrintDataLine(_supportedOptions, data, name, "", indent);
    _stageData += data;
    _stageFiles += 1;
}
