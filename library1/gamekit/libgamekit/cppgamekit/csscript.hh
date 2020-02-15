#pragma once

#include "csbehaviour.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScript, csBehaviour) {
    
    static void updateAll();
    
    virtual bool external();
    virtual std::string externalName();
    
    void handleCreate () override;
    void handleDestroy() override;
    
    virtual void handleUpdate();
    
    //user-oriented lifecycle events:
    virtual void onAwake();
    virtual void onStart();
    virtual void onUpdate();
    virtual void onDestroy();
};

_CSGAMEKIT_END_VERSION_NS
