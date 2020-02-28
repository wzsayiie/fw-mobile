#include "cqcbasis.h"
#include "cqcppbasis.hh"
#include <cfloat>
#include <cmath>

//float number comparision.
bool cq_flt_equal(float  a, float  b) {return fabsf(a - b) < FLT_EPSILON;}
bool cq_dbl_equal(double a, double b) {return fabs (a - b) < DBL_EPSILON;}

//string:

bool cq_str_empty   (const char     *s) {return s == nullptr || *s == '\0';}
bool cq_u16str_empty(const char16_t *s) {return s == nullptr || *s == '\0';}

template<class T> const T *store_str(const T *string) {
    static thread_local std::basic_string<T> *object = nullptr;
    if (object == nullptr) {
        object = new std::basic_string<T>;
    }
    
    if (string != nullptr) {
        *object = string;
    } else {
        object->clear();
    }
    
    return object->c_str();
}

const char     *cq_store_str   (const char     *s) {return store_str<char    >(s);}
const char16_t *cq_store_u16str(const char16_t *s) {return store_str<char16_t>(s);}

//unicode:

static char32_t u32c_from8s(const _char8_t *ptr, size_t *count) {
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
    for (const _char8_t *it = ptr + 1; it < ptr + *count; ++it) {
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

static u16encoded u16e_from32c(char32_t src) {
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

const char16_t *cq_u16s_from8s(const _char8_t *src) {
    if (src == nullptr) {
        return cq_store_u16str(nullptr);
    }
    
    std::u16string dst;
    while (true) {
        size_t count = 0;
        char32_t point = u32c_from8s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u16e_from32c(point).item);
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

static char32_t u32c_from16s(const char16_t *ptr, size_t *count) {
    
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
    _char8_t item[8];
};

static u8encoded u8e_from32c(char32_t src) {
    u8encoded dst;
    memset(&dst, 0, sizeof(dst));
    
    if (src <= 0x7f) {
        
        //up to 7 bit, occupy 1 byte.
        dst.item[0] = (_char8_t)src;
        
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

const _char8_t *cq_u8s_from16s(const char16_t *src) {
    if (src == nullptr) {
        return cq_store_str(nullptr);
    }
    
    std::string dst;
    while (true) {
        size_t count = 0;
        char32_t point = u32c_from16s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u8e_from32c(point).item);
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
    return cq_store_str(dst.c_str());
}

//multiplex structures:

void cq_c_bytes_receiver(cq_bytes *dst, const void *ptr, int32_t len) {
    if (dst && ptr && len > 0) {
        auto object = (std::vector<uint8_t> *)dst;
        object->insert(object->end(), (uint8_t *)ptr, (uint8_t *)ptr + len);
    }
}

void cq_c_int64s_receiver(cq_int64s *dst, int64_t value) {
    if (dst != nullptr) {
        auto object = (std::vector<int64_t> *)dst;
        object->push_back(value);
    }
}

void cq_c_strings_receiver(cq_strings *dst, const char *value) {
    if (dst && value) {
        auto object = (std::vector<std::string> *)dst;
        object->push_back(value);
    }
}

void cq_c_ss_map_receiver(cq_ss_map *dst, const char *key, const char *value) {
    if (dst && key && value) {
        auto object = (std::map<std::string, std::string> *)dst;
        (*object)[key] = value;
    }
}

void cq_c_bytes_sender(cq_bytes *src, cq_bytes_receiver recv, cq_bytes *dst) {
    if (src && recv) {
        auto object = (std::vector<uint8_t> *)src;
        recv(dst, object->data(), (int32_t)object->size());
    }
}

void cq_c_int64s_sender(cq_int64s *src, cq_int64s_receiver recv, cq_int64s *dst) {
    if (src && recv) {
        auto object = (std::vector<int64_t> *)src;
        for (auto &it : *object) {
            recv(dst, it);
        }
    }
}

void cq_c_strings_sender(cq_strings *src, cq_strings_receiver recv, cq_strings *dst) {
    if (src && recv) {
        auto object = (std::vector<std::string> *)src;
        for (auto &it : *object) {
            recv(dst, it.c_str());
        }
    }
}

void cq_c_ss_map_sender(cq_ss_map *src, cq_ss_map_receiver recv, cq_ss_map *dst) {
    if (src && recv) {
        auto object = (std::map<std::string, std::string> *)src;
        for (auto &cp : *object) {
            recv(dst, cp.first.c_str(), cp.second.c_str());
        }
    }
}

cq_bytes *cq_store_c_bytes(cq_bytes_sender send, cq_bytes *src) {
    static thread_local std::vector<uint8_t> *object = nullptr;
    if (object == nullptr) {
        object = new std::vector<uint8_t>;
    }
    
    auto dst = (cq_bytes *)object;
    
    object->clear();
    if (send) {
        send(src, cq_c_bytes_receiver, dst);
    }
    
    return dst;
}

cq_int64s *cq_store_c_int64s(cq_int64s_sender send, cq_int64s *src) {
    static thread_local std::vector<int64_t> *object = nullptr;
    if (object == nullptr) {
        object = new std::vector<int64_t>;
    }
    
    auto dst = (cq_int64s *)object;
    
    object->clear();
    if (send) {
        send(src, cq_c_int64s_receiver, dst);
    }
    
    return dst;
}

cq_strings *cq_store_c_strings(cq_strings_sender send, cq_strings *src) {
    static thread_local std::vector<std::string> *object = nullptr;
    if (object == nullptr) {
        object = new std::vector<std::string>;
    }
    
    auto dst = (cq_strings *)object;
    
    object->clear();
    if (send) {
        send(src, cq_c_strings_receiver, dst);
    }
    
    return dst;
}

cq_ss_map *cq_store_c_ss_map(cq_ss_map_sender send, cq_ss_map *src) {
    static thread_local std::map<std::string, std::string> *object = nullptr;
    if (object == nullptr) {
        object = new std::map<std::string, std::string>;
    }
    
    auto dst = (cq_ss_map *)object;
    
    object->clear();
    if (send) {
        send(src, cq_c_ss_map_receiver, dst);
    }
    
    return dst;
}

//object reference:

struct cq_obj {
    void *raw = nullptr;
    void (*release)(void *) = nullptr;
    
    std::string cls;
    int32_t magic = 0;
};

cq_obj *cq_retain_raw_obj(void *raw, void (*release)(void *raw)) {
    cq_obj *obj = nullptr;
    if (raw && release) {
        obj = new cq_obj;
        obj->raw = raw;
        obj->release = release;
    }
    return obj;
}

//cq_obj *cq_retain_obj(cq_obj *obj) {
//}

void cq_release_obj(cq_obj *obj) {
    if (obj != nullptr) {
        obj->release(obj->raw);
        delete obj;
    }
}

void *cq_obj_raw(cq_obj *obj) {
    if (obj != nullptr) {
        return obj->raw;
    } else {
        return nullptr;
    }
}

void cq_set_obj_cls(cq_obj *obj, const char *cls) {
    if (obj != nullptr) {
        obj->cls = cls ? cls : "";
    }
}

const char *cq_obj_cls(cq_obj *obj) {
    if (obj != nullptr) {
        return obj->cls.c_str();
    } else {
        return nullptr;
    }
}

void cq_set_obj_magic(cq_obj *obj, int32_t magic) {
    if (obj != nullptr) {
        obj->magic = magic;
    }
}

int32_t cq_obj_magic(cq_obj *obj) {
    if (obj != nullptr) {
        return obj->magic;
    } else {
        return 0;
    }
}
