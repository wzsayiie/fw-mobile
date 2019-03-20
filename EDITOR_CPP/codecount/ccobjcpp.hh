#pragma once

#include "cctraverser.hh"

//NOTE:
//if Line Splicing ('\' at end of one line) appear in comment or string literal,
//ccObjcpp can not work correctly.

struct ccObjcpp : ccTraverser {
    
    void onGetSupportedFiles(vector<string> *out) override;
    void onGetSupportedOptions(ccStatisticsMask *out) override;
    void onHandleFile(const vector<char> &bytes, ccStatisticsData *result) override;
};
