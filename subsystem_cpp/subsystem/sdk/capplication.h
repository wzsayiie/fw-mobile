#pragma once

#include "clanguage.h"

c_interface(CActivityCallbacks, CInterface) {

    virtual void onCreated  () {}
    virtual void onStarted  () {}
    virtual void onRestarted() {}
    virtual void onResumed  () {}
    virtual void onPaused   () {}
    virtual void onStopped  () {}
};

struct CApplication {
    
    static CApplication *get();
    
    CApplication();
    ~CApplication();
    
    void registerActivityCallbacks(CActivityCallbacks *callbacks);
    
    void onCreate ();
    void onStart  ();
    void onRestart();
    void onResume ();
    void onPause  ();
    void onStop   ();
    
private:
    
    struct _CApplicationData *self;
};
