#pragma once

#include "csbehaviour.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScript, csBehaviour) {
    
    static void updateAllScripts();
    
    virtual bool external();
    virtual std::string externalName();
    
    /*old*/ void handleCreate () override;
    virtual void handleUpdate () /*new */;
    /*old*/ void handleDestroy() override;
    
    //user-oriented lifecycle events:
    virtual void awake();
    virtual void start();
    virtual void update();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
