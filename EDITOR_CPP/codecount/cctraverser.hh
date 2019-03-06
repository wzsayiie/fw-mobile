#pragma once

#include "utility.hh"

using CCMask = int;
const CCMask CCMaskCodeLine    = 0x1;
const CCMask CCMaskCodeAndCmnt = 0x2;
const CCMask CCMaskCommentLine = 0x4;
const CCMask CCMaskEmptyLine   = 0x8;

struct CCData {
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
    virtual void onGetSupportedOptions(CCMask *out) = 0;
    virtual void onHandleFile(const vector<char> &bytes, CCData *result) = 0;
    
private:
    
    vector<string> _supportedFiles;
    CCMask _supportedOptions;
    
    CCData _globalData;
    int _globalFiles;
    
    CCData _stageData;
    int _stageFiles;
};
