#pragma once

#include "traverser.hh"

struct GeneralTraverser : Traverser {
    
    void onStart(vector<string> *outTypes, string *outDefaultTag) override;
    
    void onBeginTask() override;
    void onHandleFile(const string &file, string *outTag) override;
    void onEndTask() override;
    
    void onStop() override;
    
private:
    
    int _tFiles;
    int _tCodes;
    int _tEmpties;
    
    int _aFiles;
    int _aCodes;
    int _aEmpties;
};
