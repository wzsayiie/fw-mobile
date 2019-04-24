#include "cqcbasis.h"

extern const bool cq_on_android = CQ_ON_ANDROID;
extern const bool cq_on_iphone  = CQ_ON_IPHONE ;
extern const bool cq_on_osx     = CQ_ON_OSX    ;
extern const bool cq_on_windows = CQ_ON_WINDOWS;

static thread_local char *_string_stored_string = nullptr;
static thread_local int32_t _string_stored_size = 0;

const char *cq_string_store_string(const char *value) {
    auto size = (int32_t)(value ? strlen(value) : 0);
    return cq_string_store_bytes(value, size);
}

const char *cq_string_store_bytes(const char *bytes, int32_t size) {
    if (bytes != nullptr && size > 0) {
        _string_stored_string = (char *)realloc(_string_stored_string, size + 1);
        memcpy(_string_stored_string, bytes, size);
        _string_stored_string[size] = '\0';
        _string_stored_size = size;
    } else {
        free(_string_stored_string);
        _string_stored_string = nullptr;
        _string_stored_size = 0;
    }
    return _string_stored_string;
}

const char *cq_string_get_stored_string(void) {
    return _string_stored_string;
}

int32_t cq_string_get_stored_size(void) {
    return _string_stored_size;
}
