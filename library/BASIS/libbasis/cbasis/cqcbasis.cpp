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

//unicode:

static char32_t u32cfrom8s(const char *ptr, int32_t *count) {
    char32_t ch = 0;

    //utf-8 first byte:
    //
    // 1 byte  occupied,  7 valid bits: 0xxx'xxxx
    // 2 bytes occupied, 11 valid bits: 110x'xxxx 10xx xxxx ...
    // 3 bytes occupied, 16 valid bits: 1110'xxxx 10xx xxxx ...
    // 4 bytes occupied, 21 valid bits: 1111'0xxx 10xx xxxx ...
    //
    if /**/ ((*ptr & 0b10'00'0000) == 0b00'00'0000) { *count = 1; ch = *ptr & 0b01'11'1111;}
    else if ((*ptr & 0b11'10'0000) == 0b11'00'0000) { *count = 2; ch = *ptr & 0b00'01'1111;}
    else if ((*ptr & 0b11'11'0000) == 0b11'10'0000) { *count = 3; ch = *ptr & 0b00'00'1111;}
    else if ((*ptr & 0b11'11'1000) == 0b11'11'0000) { *count = 4; ch = *ptr & 0b00'00'0111;}
    else {
        *count = 0;
        return 0;
    }
    
    //followed bytes: 10xx'xxxx
    for (const char *it = ptr + 1; it < ptr + *count; ++it) {
        if ((*it & 0b11'00'0000) != 0b10'00'0000) {
            *count = 0;
            return 0;
        }
        ch <<= 6;
        ch |= (*it & 0b01'11'1111);
    }
    
    return ch;
}

struct u16encoded {
    char16_t item[4];
};

static u16encoded u16efrom32c(char32_t src) {
    u16encoded dst;
    memset(&dst, 0, sizeof(dst));
    
    //utf-16 surrogate pair (4 bytes):
    //
    //  1st 2 bytes: 1101 10 xx,xxxx xxxx
    //  2nd 2 bytes: 1101 11 xx,xxxx xxxx
    //
    if (src > 0xffFF) {
        
        //the biggest point of unicode is 0x10FFff (the last of 16st plane),
        //when a point subtracted from 0x10000, the remaining value will not exceed 20 bit.
        src -= 0x10000;
        dst.item[0] = ((src >> 10) & 0x3ff) | 0xd800;
        dst.item[1] = ((src      ) & 0x3ff) | 0xdc00;
    }
    //BMP character, 2 bytes.
    else {
        dst.item[0] = (char16_t)src;
    }
    
    return dst;
}

const char16_t *cq_u16sfrom8s(const char *src) {
    if (src == nullptr) {
        return nullptr;
    }
    
    std::u16string dst;
    while (true) {
        int32_t count = 0;
        char32_t point = u32cfrom8s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u16efrom32c(point).item);
                src += count;
            } else {
                //string end
                break;
            }
        } else {
            //error happened.
            //don't call dst.clear(), keep the available part.
            break;
        }
    }
    return cq_store_u16str(dst.c_str());
}

static char32_t u32cfrom16s(const char16_t *ptr, int32_t *count) {
    
    //utf-16 surrogate pair (4 bytes):
    //
    //  1st 2 bytes: 1101 10 xx,xxxx xxxx
    //  2nd 2 bytes: 1101 11 xx,xxxx xxxx
    //
    if (/**/0xd800 <= ptr[0] && ptr[0] <= 0xdbff) {
        if (0xdc00 <= ptr[1] && ptr[1] <= 0xdfff) {
            *count = 2;
            char32_t ch = 0;
            ch = (char32_t)(ptr[0] & 0x03ff);
            ch = (char32_t)(ptr[1] & 0x03ff) | (ch << 10);
            return ch + 0x10000;
        } else {
            //error happened
            *count = 0;
            return 0;
        }
    }
    //BMP character, 2 bytes.
    else {
        *count = 1;
        return (char32_t)*ptr;
    }
}

struct u8encoded {
    char item[8];
};

static u8encoded u8efrom32c(char32_t src) {
    u8encoded dst;
    memset(&dst, 0, sizeof(dst));
    
    if (src <= 0x7f) {
        
        //up to 7 bit, occupy 1 byte.
        dst.item[0] = (char)src;
        
    } else if (src <= 0x7ff) {
        
        //up to 11 bit, occupy 2 bytes.
        dst.item[0] = ((src >> 6) & 0b00'01'1111) | 0b11'00'0000;
        dst.item[1] = ((src     ) & 0b00'11'1111) | 0b10'00'0000;
        
    } else if (src <= 0xffFF) {
        
        //up to 16 bit, occupy 3 bytes.
        dst.item[0] = ((src >> 12) & 0b00'00'1111) | 0b11'10'0000;
        dst.item[1] = ((src >>  6) & 0b00'11'1111) | 0b10'00'0000;
        dst.item[2] = ((src      ) & 0b00'11'1111) | 0b10'00'0000;
        
    } else if (src <= 0x10FFff) {
        
        //up to 21 bit, occupy 4 bytes.
        dst.item[0] = ((src >> 18) & 0b00'00'0111) | 0b11'11'0000;
        dst.item[1] = ((src >> 12) & 0b00'11'1111) | 0b10'00'0000;
        dst.item[2] = ((src >>  6) & 0b00'11'1111) | 0b10'00'0000;
        dst.item[3] = ((src      ) & 0b00'11'1111) | 0b10'00'0000;
    }
    
    return dst;
}

const char *cq_u8sfrom16s(const char16_t *src) {
    if (src == nullptr) {
        return nullptr;
    }
    
    std::string dst;
    while (true) {
        int32_t count = 0;
        char32_t point = u32cfrom16s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u8efrom32c(point).item);
                src += count;
            } else {
                //string end
                break;
            }
        } else {
            //error happened.
            //don't call dst.clear(), keep the available part.
            break;
        }
    }
    return cq_store_u8str(dst.c_str());
}
