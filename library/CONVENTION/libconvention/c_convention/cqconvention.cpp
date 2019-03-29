#include "cqconvention.h"

static thread_local char *_string_stored_bytes = nullptr;
static thread_local int32_t _string_stored_size = 0;

const char *cq_string_store_string(const char *value) {
    auto size = (int32_t)(value ? strlen(value) : 0);
    return cq_string_store_bytes(value, size);
}

const char *cq_string_store_bytes(const char *bytes, int32_t size) {
    if (bytes != nullptr) {
        _string_stored_bytes = (char *)realloc(_string_stored_bytes, size + 1);
        strcpy(_string_stored_bytes, bytes);
        _string_stored_size = size;
    } else {
        free(_string_stored_bytes);
        _string_stored_bytes = nullptr;
        _string_stored_size = 0;
    }
    return _string_stored_bytes;
}

const char *cq_string_get_stored_bytes(void) {
    return _string_stored_bytes;
}

int32_t cq_string_get_stored_size(void) {
    return _string_stored_size;
}
