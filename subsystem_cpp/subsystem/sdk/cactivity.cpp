#include "cactivity.h"
#include "capplication.h"

#define NAMESPACE_BEGIN namespace {
#define NAMESPACE_END   }

NAMESPACE_BEGIN

struct MainCallbacks : CActivityCallbacks {
    
    CActivity *_activity;
    
    MainCallbacks(CActivity *activity);
    
    void onCreated  () override;
    void onStarted  () override;
    void onRestarted() override;
    void onResumed  () override;
    void onPaused   () override;
    void onStopped  () override;
};

MainCallbacks::MainCallbacks(CActivity *activity) {
    _activity = activity;
}

void MainCallbacks::onCreated  () { _activity->onCreate (); }
void MainCallbacks::onStarted  () { _activity->onStart  (); }
void MainCallbacks::onRestarted() { _activity->onRestart(); }
void MainCallbacks::onResumed  () { _activity->onResume (); }
void MainCallbacks::onPaused   () { _activity->onPause  (); }
void MainCallbacks::onStopped  () { _activity->onStop   (); }

NAMESPACE_END

void CActivityMain(CActivity *activity) {
    if (activity != nullptr) {
    }
}
