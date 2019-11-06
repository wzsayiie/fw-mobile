#include "cqwnd.h"
#include "cqcppbasis.hh"

static cq_wnd *wnd_store(int64_t wid, cq_wnd *wnd, char intent) {
    static std::map<int64_t, cq_wnd *> *store = nullptr;
    if (store == nullptr) {
        store = new std::map<int64_t, cq_wnd *>;
    }
    
    switch (intent) {
        case '+' /* add */: {
            if (wid != 0 && wnd != nullptr) {
                store->insert(std::make_pair(wid, wnd));
            }
            return nullptr;
        }
        case '?' /* get */: {
            if (store->find(wid) != store->end()) {
                return store->at(wid);
            } else {
                return nullptr;
            }
        }
        case '-' /* remove */: {
            store->erase(wid);
            return nullptr;
        }
        default: {
            return nullptr;
        }
    }
}
static void add_wnd(int64_t wid, cq_wnd *wnd) {
    wnd_store(wid, wnd, '+');
}
static cq_wnd *get_wnd(int64_t wid) {
    return wnd_store(wid, nullptr, '?');
}

struct cq_wnd {
    cq_wndproc proc;
    
    float x;
    float y;
    float width;
    float height;
    
    bool loaded;
    bool visible;
    bool touching;
    
    int64_t wid;
    int64_t extra;
};

static _cq_wndport _wndport = {nullptr};

float cq_wnd_scale() {
    static float scale = 0;
    if (cq_flt_equal(scale, 0) && _wndport.wnd_scale) {
        scale = _wndport.wnd_scale();
    }
    return scale;
}

cq_wnd *cq_new_wnd() {
    if (_wndport.new_wnd) {
        if (int64_t wid = _wndport.new_wnd()) {
            auto wnd = (cq_wnd *)calloc(1, sizeof(cq_wnd));
            wnd->wid = wid;
            add_wnd(wid, wnd);
            return wnd;
        }
    }
    return nullptr;
}

void cq_show_wnd(cq_wnd *wnd) {
    if (wnd && _wndport.show_wnd) {
        _wndport.show_wnd(wnd->wid);
    }
}

void cq_set_wndproc(cq_wnd *wnd, cq_wndproc *proc) {
    if (wnd && proc) {
        wnd->proc = *proc;
    }
}

void cq_set_wnd_extra(cq_wnd *wnd, int64_t extra) {
    if (wnd != nullptr) {
        wnd->extra = extra;
    }
}
int64_t cq_wnd_extra(cq_wnd *wnd) {
    if (wnd != nullptr) {
        return wnd->extra;
    } else {
        return 0;
    }
}

bool cq_wnd_loaded (cq_wnd *w) {return w ? w->loaded  : false;}
bool cq_wnd_visible(cq_wnd *w) {return w ? w->visible : false;}

float cq_wnd_x     (cq_wnd *w) {return w ? w->x      : 0.f;}
float cq_wnd_y     (cq_wnd *w) {return w ? w->y      : 0.f;}
float cq_wnd_width (cq_wnd *w) {return w ? w->width  : 0.f;}
float cq_wnd_height(cq_wnd *w) {return w ? w->height : 0.f;}

void _cq_init_wndport(_cq_wndport *port) {
    if (port != nullptr) {
        _wndport = *port;
    }
}

template<class F, class... A> void notify(F f, A... a) {
    if (f != nullptr) {
        f(a...);
    }
}

void _cq_wnd_load(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (!wnd->loaded) {
            wnd->loaded = true;
            notify(wnd->proc.load, wnd);
        }
    }
}

void _cq_wnd_appear(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->loaded && !wnd->visible) {
            notify(wnd->proc.appear, wnd);
            wnd->visible = true;
        }
    }
}

void _cq_wnd_disappear(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->loaded && wnd->visible) {
            wnd->visible = false;
            notify(wnd->proc.disappear, wnd);
        }
    }
}

void _cq_wnd_unload(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->loaded) {
            notify(wnd->proc.unload, wnd);
            wnd->loaded = false;
        }
    }
}

void _cq_wnd_origin(int64_t wid, float x, float y) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        wnd->x = x;
        wnd->y = y;
        if (wnd->loaded) {
            notify(wnd->proc.move, wnd, x, y);
        }
    }
}

void _cq_wnd_size(int64_t wid, float width, float height) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        wnd->width  = width;
        wnd->height = height;
        if (wnd->loaded) {
            notify(wnd->proc.resize, wnd, width, height);
        }
    }
}

void _cq_wnd_update(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->loaded) {
            notify(wnd->proc.update, wnd);
        }
    }
}

void _cq_wnd_gldraw(int64_t wid) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->loaded) {
            notify(wnd->proc.gldraw, wnd);
        }
    }
}

void _cq_wnd_pbegan(int64_t wid, float x, float y) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->visible && !wnd->touching) {
            wnd->touching = true;
            notify(wnd->proc.pbegan, wnd, x, y);
        }
    }
}

void _cq_wnd_pmoved(int64_t wid, float x, float y) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->touching) {
            notify(wnd->proc.pmoved, wnd, x, y);
        }
    }
}

void _cq_wnd_pended(int64_t wid, float x, float y) {
    if (cq_wnd *wnd = get_wnd(wid)) {
        if (wnd->touching) {
            notify(wnd->proc.pended, wnd, x, y);
            wnd->touching = false;
        }
    }
}
