#pragma once

#include "cctraverser.hh"

struct ccGeneral : ccTraverser {
    
    void onGetSupportedFiles(vector<string> *out) override;
    void onGetSupportedOptions(ccStatisticsMask *out) override;
    void onHandleFile(const vector<char> &bytes, ccStatisticsData *result) override;
};
