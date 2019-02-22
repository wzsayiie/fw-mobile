#pragma once

#include "utility.hh"

struct Traverser : CQTraverserDelegate {
    
    static void count(const vector<string> &paths, Traverser *traverser);
    
    string traverserGetDefaultTag() override final;
    bool traverserFindFile(const string &file, string *outTag) override final;
    
    //format by thousands separator
    static const char *ts(int n);
    
protected:
    
    //lifecycle:
    //
    //onStart
    //
    //  onBeginTask     task A
    //    onHandleFile  file A1
    //    onHandleFile  file A2
    //    ...           ...
    //  onEndTask
    //
    //  onBeginTask     task B
    //    onHandleFile  file B1
    //    onHandleFile  file B2
    //    ...           ...
    //  onEndTask
    //
    //  ...
    //
    //onStop
    
    virtual void onStart(vector<string> *outTypes, string *outDefaultTag) = 0;
    
    virtual void onBeginTask() = 0;
    virtual void onHandleFile(const string &file, string *outTag) = 0;
    virtual void onEndTask() = 0;
    
    virtual void onStop() = 0;
    
private:
    
    vector<string> _types;
    string _defaultTag;
};
