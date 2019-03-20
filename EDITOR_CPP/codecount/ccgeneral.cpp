#include "ccgeneral.hh"

static void ScanSource(const vector<char> &bytes, int *codeLine, int *emptyLine) {
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    
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

void CCGeneral::onGetSupportedFiles(vector<string> *out) {
    *out = {".java", ".h", ".hh", ".m", ".mm", ".cpp", ".cs", ".lua"};
}

void CCGeneral::onGetSupportedOptions(CCStatisticsMask *out) {
    *out = CCStatisticsMaskCodeLine | CCStatisticsMaskEmptyLine;
}

void CCGeneral::onHandleFile(const vector<char> &bytes, CCStatisticsData *result) {
    ScanSource(bytes, &result->codeLine, &result->emptyLine);
}
