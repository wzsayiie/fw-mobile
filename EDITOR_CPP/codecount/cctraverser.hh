#pragma once

#include "utility.hh"

//auxiliary functions

CQError CCReadUTF8File(const string &path, const vector<string> &types, vector<char> *out);

const char *CCFormatted(int number);

int CCPercent(int part, int total);

//traverser

struct CCGlobal : object { protected: CCGlobal() = default; };
struct CCStage  : object { protected: CCStage () = default; };

struct CCData {
    CCGlobal *global = nullptr;
    CCStage  *stage  = nullptr;
};

struct CCTraverser : CQTraverserDelegate {
    
public:
    
    void count(const vector<string> &paths);
    
    void traverserGetDirectory(const string &name, int indent) override;
    void traverserGetFile     (const string &name, int indent) override;
    
protected:
    
    virtual void onBegin     (CCData *data) = 0;
    virtual void onBeginStage(CCData *data) = 0;
    
    virtual void onHandleDirectory(CCData *data, const string &name, int indent) = 0;
    virtual void onHandleFile     (CCData *data, const string &name, int indent) = 0;
    
    virtual void onEndStage(CCData *data) = 0;
    virtual void onEnd     (CCData *data) = 0;
    
private:
    
    CCData _data;
};
