#pragma once

#include "cctraverser.hh"

struct CCCSharpTraverser : CCTraverser {
    
protected:

    void onBegin     (CCData *data) override;
    void onBeginStage(CCData *data) override;
    
    void onHandleDirectory(CCData *data, const string &name, int indent) override;
    void onHandleFile     (CCData *data, const string &name, int indent) override;
    
    void onEndStage(CCData *data) override;
    void onEnd     (CCData *data) override;
};
