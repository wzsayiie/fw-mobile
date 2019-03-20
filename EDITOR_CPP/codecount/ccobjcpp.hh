#pragma once

#include "cctraverser.hh"

//NOTE:
//if Line Splicing ('\' at end of one line) appear in comment or string literal,
//CCObjcpp can not work correctly.

struct CCObjcpp : CCTraverser {
    
    void onGetSupportedFiles(vector<string> *out) override;
    void onGetSupportedOptions(CCStatisticsMask *out) override;
    void onHandleFile(const vector<char> &bytes, CCStatisticsData *result) override;
};
