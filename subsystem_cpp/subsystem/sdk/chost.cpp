#include "chost_p.h"

using namespace std;

static map<CHostEvent, vector<CHostListener>> *eventListeners() {
    static map<CHostEvent, vector<CHostListener>> *object = nullptr;
    if (object == nullptr) {
        object = new map<CHostEvent, vector<CHostListener>>;
    }
    return object;
}

void CHostAddListener(CHostEvent event, CHostListener listener) {
    auto list = eventListeners();
    
    if (list->find(event) == list->end()) {
        (*list)[event] = vector<CHostListener>();
    }
    (*list)[event].push_back(listener);
}

void CHostOnEvent(CHostEvent event) {
    auto list = eventListeners();
    if (list->find(event) == list->end()) {
        return;
    }
    
    for (auto it : (*list)[event]) {
        it(event);
    }
}
