#pragma once

struct CActivity {
    
    virtual ~CActivity() {}
    
    virtual void onCreate ();
    virtual void onStart  ();
    virtual void onRestart();
    virtual void onResume ();
    virtual void onPause  ();
    virtual void onStop   ();
};

void CActivityMain(CActivity *ativity);
