#pragma once

#include "cctraverser.hh"

struct CCGeneral : CCTraverser {
    
    void onGetSupportedFiles(vector<string> *out) override;
    void onGetSupportedOptions(CCMask *out) override;
    void onHandleFile(const vector<char> &bytes, CCData *result) override;
};
