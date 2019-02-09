#include "cqhost_p.hh"

using namespace std;

static map<CQHostEvent, vector<CQHostListener>> *eventListeners() {
    static map<CQHostEvent, vector<CQHostListener>> *object = nullptr;
    if (object == nullptr) {
        object = new map<CQHostEvent, vector<CQHostListener>>;
    }
    return object;
}

void CQHostAddListener(CQHostEvent event, CQHostListener listener) {
    auto list = eventListeners();
    
    if (list->find(event) == list->end()) {
        (*list)[event] = vector<CQHostListener>();
    }
    (*list)[event].push_back(listener);
}

void CQHostOnEvent(CQHostEvent event) {
    auto list = eventListeners();
    if (list->find(event) == list->end()) {
        return;
    }
    
    for (auto it : (*list)[event]) {
        it(event);
    }
}
