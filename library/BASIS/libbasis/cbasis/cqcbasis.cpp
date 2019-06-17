#include "cqcbasis.h"

extern const bool cq_on_android = CQ_ON_ANDROID;
extern const bool cq_on_iphone  = CQ_ON_IPHONE ;
extern const bool cq_on_osx     = CQ_ON_OSX    ;
extern const bool cq_on_windows = CQ_ON_WINDOWS;

void _cq_assign_data(_cq_data *data, const void *bytes, int32_t size) {
    if (data == nullptr) {
        return;
    }
    
    if (bytes != nullptr && size > 0) {
        data->bytes = (char *)realloc(data->bytes, size + 1);
        memcpy(data->bytes, bytes, size);
        ((char *)data->bytes)[size] = '\0';
        data->size = size;
    } else {
        free(data->bytes);
        data->bytes = nullptr;
        data->size = 0;
    }
}

void _cq_clear_data(_cq_data *data) {
    if (data != nullptr) {
        free(data->bytes);
        data->bytes = nullptr;
        data->size = 0;
    }
}

bool cq_null_or_emptry(const char *string) {
    return string == nullptr || *string == '\0';
}

static thread_local _cq_data _stored = {nullptr, 0};

const char *cq_store_string(const char *value) {
    auto size = (int32_t)(value ? strlen(value) : 0);
    _cq_assign_data(&_stored, value, size);
    return (const char *)_stored.bytes;
}

const void *cq_store_bytes(const void *bytes, int32_t size) {
    _cq_assign_data(&_stored, bytes, size);
    return _stored.bytes;
}

const char *cq_stored_string() {
    return (const char *)_stored.bytes;
}

const void *cq_stored_bytes() {
    return _stored.bytes;
}

int32_t cq_stored_size() {
    return _stored.size;
}
