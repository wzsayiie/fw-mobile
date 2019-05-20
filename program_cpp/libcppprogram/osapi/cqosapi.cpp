#include "cqosapi.h"
#include "cqcppbasis.hh"

static float (*_window_get_width       )(int64_t) = nullptr;
static float (*_window_get_height      )(int64_t) = nullptr;
static float (*_window_get_screen_scale)(int64_t) = nullptr;

static std::map<int64_t, cq_window *> *get_window_store() {
    static std::map<int64_t, cq_window *> *store = nullptr;
    if (store == nullptr) {
        store = new std::map<int64_t, cq_window *>;
    }
    return store;
}

static void set_window_pair(int64_t idx, cq_window *window) {
    auto store = get_window_store();
    (*store)[idx] = window;
}

static cq_window *window_from_idx(int64_t idx) {
    auto store = get_window_store();
    auto it = store->find(idx);
    return it != store->end() ? it->second : nullptr;
}

static int64_t _default_window_idx = 0;

struct cq_window {
    cq_window_procedure procedure;
    int64_t idx;
    int64_t extra;
};

cq_window *cq_window_get_default() {
    return window_from_idx(_default_window_idx);
}

void cq_window_set_procedure(cq_window *window, cq_window_procedure *procedure) {
    if (window && procedure) {
        window->procedure = *procedure;
    }
}

cq_window_procedure *cq_window_get_procedure(cq_window *window) {
    return window ? &window->procedure : nullptr;
}

void cq_window_set_extra(cq_window *window, int64_t extra) {
    if (window) {
        window->extra = extra;
    }
}

int64_t cq_window_get_extra(cq_window *window) {
    return  window ? window->extra : 0;
}

float cq_window_get_width(cq_window *window) {
    if (_window_get_width && window) {
        return _window_get_width(window->idx);
    } else {
        return 0;
    }
}

float cq_window_get_height(cq_window *window) {
    if (_window_get_height && window) {
        return _window_get_height(window->idx);
    } else {
        return 0;
    }
}

float cq_window_get_screen_scale(cq_window *window) {
    if (_window_get_screen_scale && window) {
        return _window_get_screen_scale(window->idx);
    } else {
        return 0;
    }
}

void _cq_install_window_get_width_handler(float (*h)(int64_t)) {
    _window_get_width = h;
}
void _cq_install_window_get_height_handler(float (*h)(int64_t)) {
    _window_get_height = h;
}
void _cq_install_window_get_screen_scale_handler(float (*h)(int64_t)) {
    _window_get_screen_scale = h;
}

void _cq_notify_default_window_created(int64_t window_idx) {
    
    _default_window_idx = window_idx;
    
    auto window = (cq_window *)calloc(sizeof(cq_window), 1);
    window->idx = window_idx;
    set_window_pair(window_idx, window);
    
    _cq_default_window_created();
}

void _cq_notify_window_load(int64_t window_idx) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.load) {
        window->procedure.load(window);
    }
}

void _cq_notify_window_show(int64_t window_idx) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.show) {
        window->procedure.show(window);
    }
}

void _cq_notify_window_hide(int64_t window_idx) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.hide) {
        window->procedure.hide(window);
    }
}

void _cq_notify_window_touch_began(int64_t window_idx, float x, float y) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.touch_began) {
        window->procedure.touch_began(window, x, y);
    }
}

void _cq_notify_window_touch_moved(int64_t window_idx, float x, float y) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.touch_moved) {
        window->procedure.touch_moved(window, x, y);
    }
}

void _cq_notify_window_touch_ended(int64_t window_idx, float x, float y) {
    cq_window *window = window_from_idx(window_idx);
    if (window == nullptr) {
        return;
    }
    
    if (window->procedure.touch_ended) {
        window->procedure.touch_ended(window, x, y);
    }
}
