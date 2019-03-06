#pragma once

#include "cctraverser.hh"

struct CCGeneral : CCTraverser {
    
    void onGetSupportedFiles(vector<string> *out) override;
    void onGetSupportedOptions(CCStatisticsMask *out) override;
    void onHandleFile(const vector<char> &bytes, CCStatisticsData *result) override;
};
