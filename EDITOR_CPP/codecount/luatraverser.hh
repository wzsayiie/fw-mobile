#pragma once

#include "traverser.hh"

struct LuaTraverser : Traverser {
    
    void onStart(vector<string> *outTypes, string *outDefaultTag) override;
    
    void onBeginTask() override;
    void onHandleFile(const string &file, string *outTag) override;
    void onEndTask() override;
    
    void onStop() override;
};
