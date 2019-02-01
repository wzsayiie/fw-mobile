#include "capplication.h"
#include <vector>

using namespace std;

CApplication *CApplication::get() {
    static CApplication *object = nullptr;
    if (object == nullptr) {
        object = new CApplication;
    }
    return object;
}

struct _CApplicationData {
    vector<CActivityCallbacks *> activityCallbacks;
};

CApplication::CApplication() {
    self = new _CApplicationData;
}

CApplication::~CApplication() {
    delete self;
}

void CApplication::registerActivityCallbacks(CActivityCallbacks *callbacks) {
    if (callbacks != nullptr) {
        self->activityCallbacks.push_back(callbacks);
    }
}

#define IMPL(FUNC)\
/**/    for (auto it : self->activityCallbacks) {\
/**/        it->FUNC();\
/**/    }

void CApplication::onCreate () { IMPL(onCreated  ) }
void CApplication::onStart  () { IMPL(onStarted  ) }
void CApplication::onRestart() { IMPL(onRestarted) }
void CApplication::onResume () { IMPL(onResumed  ) }
void CApplication::onPause  () { IMPL(onPaused   ) }
void CApplication::onStop   () { IMPL(onStarted  ) }

#undef IMPL
