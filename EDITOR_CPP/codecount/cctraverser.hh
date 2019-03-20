#pragma once

#include "utility.hh"

using ccContentMask = int;
const ccContentMask ccContentMaskCode    = 0x1;
const ccContentMask ccContentMaskComment = 0x2;

using ccStatisticsMask = int;
const ccStatisticsMask ccStatisticsMaskCodeLine    = 0x1;
const ccStatisticsMask ccStatisticsMaskCodeAndCmnt = 0x2;
const ccStatisticsMask ccStatisticsMaskCommentLine = 0x4;
const ccStatisticsMask ccStatisticsMaskEmptyLine   = 0x8;

struct ccStatisticsData {
    int codeLine    = 0;
    int codeAndCmnt = 0;
    int commentLine = 0;
    int emptyLine   = 0;
};

struct ccTraverser : cqTraverserDelegate {
    
    void count(const vector<string> &paths);
    
    void traverserGetDirectory(const string &name, int indent) override;
    void traverserGetFile     (const string &name, int indent) override;
    
    virtual void onGetSupportedFiles(vector<string> *out) = 0;
    virtual void onGetSupportedOptions(ccStatisticsMask *out) = 0;
    virtual void onHandleFile(const vector<char> &bytes, ccStatisticsData *result) = 0;
    
private:
    
    vector<string> _supportedFiles;
    ccStatisticsMask _supportedOptions;
    
    ccStatisticsData _globalData;
    int _globalFiles;
    
    ccStatisticsData _stageData;
    int _stageFiles;
};
