#include "cqcbasis.h"
#include <string>

//data:

void _cq_assign_data(_cq_data *data, const void *items, int32_t size, int32_t count) {
    if (data == nullptr) {
        return;
    }
    
    if (items != nullptr && size > 0 && count > 0) {
        _cq_resize_data(data, size, count);
        memcpy(data->items, items, size * count);
    } else {
        _cq_clear_data(data);
    }
}

void _cq_clear_data(_cq_data *data) {
    if (data != nullptr) {
        free(data->items);
        data->items = nullptr;
        data->size  = 0;
        data->count = 0;
    }
}

void _cq_resize_data(_cq_data *data, int32_t size, int32_t count) {
    if (data == nullptr) {
        return;
    }
    
    if (size > 0 && count > 0) {
        data->items = realloc(data->items, size * (count + 1));
        memcpy((char *)data->items + size * count, "\0\0\0\0\0\0\0\0", size);
        data->size = size;
        data->count = count;
    } else {
        _cq_clear_data(data);
    }
}

//string:

bool cq_u8str_empty (const char     *s) {return s == nullptr || *s == '\0';}
bool cq_u16str_empty(const char16_t *s) {return s == nullptr || *s == '\0';}

template<class T> const T *cq_str(const T *string, char action) {
    static thread_local _cq_data store = {nullptr, 0, 0};
    if (action == '=') {
        int32_t count = 0;
        if (string != nullptr) {
            count = (int32_t)std::char_traits<T>::length(string);
        }
        _cq_assign_data(&store, string, sizeof(T), count);
    }
    return (const T *)store.items;
}

const char *cq_store_u8str(const char *s) {return cq_str<char>(s, '=');}
const char *cq_saved_u8str( /* -- -- */ ) {return cq_str<char>(0, '?');}

const char16_t *cq_store_u16str(const char16_t *s) {return cq_str<char16_t>(s, '=');}
const char16_t *cq_saved_u16str( /* -- -- --- */ ) {return cq_str<char16_t>(0, '?');}

//bytes:

static thread_local _cq_data _saved_bytes = {nullptr, 0, 0};

const void *cq_store_bytes(const void *bytes, int32_t len) {
    _cq_assign_data(&_saved_bytes, bytes, 1, len);
    return _saved_bytes.items;
}
const void *cq_saved_bytes(void) {
    return _saved_bytes.items;
}
int32_t cq_saved_bytes_len(void) {
    return _saved_bytes.count;
}
