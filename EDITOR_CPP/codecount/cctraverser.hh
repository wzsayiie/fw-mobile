#pragma once

#include "utility.hh"

using CCContentMask = int;
const CCContentMask CCContentMaskCode    = 0x1;
const CCContentMask CCContentMaskComment = 0x2;

using CCStatisticsMask = int;
const CCStatisticsMask CCStatisticsMaskCodeLine    = 0x1;
const CCStatisticsMask CCStatisticsMaskCodeAndCmnt = 0x2;
const CCStatisticsMask CCStatisticsMaskCommentLine = 0x4;
const CCStatisticsMask CCStatisticsMaskEmptyLine   = 0x8;

struct CCStatisticsData {
    int codeLine    = 0;
    int codeAndCmnt = 0;
    int commentLine = 0;
    int emptyLine   = 0;
};

struct CCTraverser : CQTraverserDelegate {
    
    void count(const vector<string> &paths);
    
    void traverserGetDirectory(const string &name, int indent) override;
    void traverserGetFile     (const string &name, int indent) override;
    
    virtual void onGetSupportedFiles(vector<string> *out) = 0;
    virtual void onGetSupportedOptions(CCStatisticsMask *out) = 0;
    virtual void onHandleFile(const vector<char> &bytes, CCStatisticsData *result) = 0;
    
private:
    
    vector<string> _supportedFiles;
    CCStatisticsMask _supportedOptions;
    
    CCStatisticsData _globalData;
    int _globalFiles;
    
    CCStatisticsData _stageData;
    int _stageFiles;
};
