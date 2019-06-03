#include "cqhostapi.h"
#include "cqcppbasis.hh"

const int ADD = 1;
const int GET = 2;

static cq_window *window_store(int64_t wid, cq_window *window, int intent) {
    static std::map<int64_t, cq_window *> *store = nullptr;
    if (store == nullptr) {
        store = new std::map<int64_t, cq_window *>;
    }
    
    switch (intent) {
        case ADD: {
            if (wid != 0 && window != nullptr) {
                store->insert(std::make_pair(wid, window));
            }
            return nullptr;
        }
        case GET: {
            if (store->find(wid) != store->end()) {
                return store->at(wid);
            } else {
                return nullptr;
            }
        }
        default: {
            return nullptr;
        }
    }
}
static void add_window(int64_t wid, cq_window *window) {
    window_store(wid, window, ADD);
}
static cq_window *get_window(int64_t wid) {
    return window_store(wid, nullptr, GET);
}

struct cq_window {
    cq_procedure procedure;
    
    float scale;
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

static _cq_interfaces _interfaces = {nullptr};

cq_window *cq_create_window() {
    if (_interfaces.create_window) {
        if (int64_t wid = _interfaces.create_window()) {
            auto window = (cq_window *)calloc(1, sizeof(cq_window));
            window->wid = wid;
            add_window(wid, window);
            return window;
        }
    }
    return nullptr;
}

void cq_show_window(cq_window *window) {
    if (window && _interfaces.show_window) {
        _interfaces.show_window(window->wid);
    }
}

void cq_set_procedure(cq_window *window, cq_procedure *procedure) {
    if (window && procedure) {
        window->procedure = *procedure;
    }
}

void cq_set_window_extra(cq_window *window, int64_t extra) {
    if (window != nullptr) {
        window->extra = extra;
    }
}
int64_t cq_window_extra(cq_window *window) {
    if (window != nullptr) {
        return window->extra;
    } else {
        return 0;
    }
}

bool cq_window_loaded (cq_window *w) {return w ? w->loaded  : false;}
bool cq_window_visible(cq_window *w) {return w ? w->visible : false;}

float cq_window_scale (cq_window *w) {return w ? w->scale  : 0.f;}
float cq_window_x     (cq_window *w) {return w ? w->x      : 0.f;}
float cq_window_y     (cq_window *w) {return w ? w->y      : 0.f;}
float cq_window_width (cq_window *w) {return w ? w->width  : 0.f;}
float cq_window_height(cq_window *w) {return w ? w->height : 0.f;}

void _cq_install_interfaces(_cq_interfaces *interfaces) {
    if (interfaces != nullptr) {
        _interfaces = *interfaces;
    }
}

template<class F, class... A> void notify(F f, A... a) {
    if (f != nullptr) {
        f(a...);
    }
}

static void (*_entry)() = nullptr;

_cq_set_entry::_cq_set_entry(void (*entry)()) {
    _entry = entry;
}

void _cq_notify_app_launch() {
    if (_entry) {
        _entry();
    }
}

void _cq_notify_window_load(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (!window->loaded) {
            window->loaded = true;
            notify(window->procedure.load, window);
        }
    }
}

void _cq_notify_window_appear(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (window->loaded && !window->visible) {
            notify(window->procedure.appear, window);
            window->visible = true;
        }
    }
}

void _cq_notify_window_disappear(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (window->loaded && window->visible) {
            window->visible = false;
            notify(window->procedure.disappear, window);
        }
    }
}

void _cq_notify_window_unload(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (window->loaded) {
            notify(window->procedure.unload, window);
            window->loaded = false;
        }
    }
}

void _cq_notify_window_scale(int64_t wid, float scale) {
    if (cq_window *window = get_window(wid)) {
        window->scale = scale;
    }
}

void _cq_notify_window_origin(int64_t wid, float x, float y) {
    if (cq_window *window = get_window(wid)) {
        window->x = x;
        window->y = y;
        if (window->loaded) {
            notify(window->procedure.move, window, x, y);
        }
    }
}

void _cq_notify_window_size(int64_t wid, float width, float height) {
    if (cq_window *window = get_window(wid)) {
        window->width  = width;
        window->height = height;
        if (window->loaded) {
            notify(window->procedure.resize, window, width, height);
        }
    }
}

void _cq_notify_window_gl_draw(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (window->loaded) {
            notify(window->procedure.gl_draw, window);
        }
    }
}

void _cq_notify_window_update(int64_t wid) {
    if (cq_window *window = get_window(wid)) {
        if (window->loaded) {
            notify(window->procedure.update, window);
        }
    }
}

void _cq_notify_window_touch_began(int64_t wid, float x, float y) {
    if (cq_window *window = get_window(wid)) {
        if (window->visible && !window->touching) {
            window->touching = true;
            notify(window->procedure.touch_began, window, x, y);
        }
    }
}

void _cq_notify_window_touch_moved(int64_t wid, float x, float y) {
    if (cq_window *window = get_window(wid)) {
        if (window->touching) {
            notify(window->procedure.touch_moved, window, x, y);
        }
    }
}

void _cq_notify_window_touch_ended(int64_t wid, float x, float y) {
    if (cq_window *window = get_window(wid)) {
        if (window->touching) {
            notify(window->procedure.touch_ended, window, x, y);
            window->touching = false;
        }
    }
}
