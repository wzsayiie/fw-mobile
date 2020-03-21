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

static char32_t u32c_from_u8s(const char *ptr, size_t *count) {
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

static char32_t u32c_from_u16s(const char16_t *ptr, size_t *count) {
    
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

struct u8encoded  {char     item[8];};
struct u16encoded {char16_t item[4];};

static u16encoded u16e_from_u32c(char32_t src) {
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

static u8encoded u8e_from_u32c(char32_t src) {
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

const char16_t *cq_u16s_from_u8s(const char *src) {
    if (src == nullptr) {
        return cq_store_u16str(nullptr);
    }
    
    std::u16string dst;
    while (true) {
        size_t count = 0;
        char32_t point = u32c_from_u8s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u16e_from_u32c(point).item);
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

const char *cq_u8s_from_u16s(const char16_t *src) {
    if (src == nullptr) {
        return cq_store_str(nullptr);
    }
    
    std::string dst;
    while (true) {
        size_t count = 0;
        char32_t point = u32c_from_u16s(src, &count);
        if (count > 0) {
            if (point != '\0') {
                dst.append(u8e_from_u32c(point).item);
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

//block:

struct block_param {
    cq_type type = CQ_TYPE_NULL;
    void *value = nullptr;
};

static thread_local std::map<std::string, block_param> *_block_params = nullptr;

void cq_set_block_param(const char *name, cq_type type, void *value) {
    if (cq_str_empty(name)) {
        return;
    }
    if (value == nullptr) {
        return;
    }
    
    if (_block_params == nullptr) {
        _block_params = new std::map<std::string, block_param>;
    }
    
    block_param param; {
        param.type  = type ;
        param.value = value;
    }
    (*_block_params)[name] = param;
}

void *cq_block_param(const char *name, cq_type type) {
    if (cq_str_empty(name)) {
        return nullptr;
    }
    if (_block_params == nullptr) {
        return nullptr;
    }
    if (cqMap::dontContain(*_block_params, name)) {
        return nullptr;
    }
    
    block_param param = (*_block_params)[name];
    if (param.type != type) {
        return nullptr;
    }
    
    return param.value;
}

void cq_run_block(cq_block block, void *data) {
    if (block != nullptr) {
        block(data);
    }
    delete _block_params;
    _block_params = nullptr;
}

//object reference:

struct event_info {
    cq_block block = nullptr;
    void *data = nullptr;
};

struct cq_obj {
    void (*release)(void *) = nullptr;
    int32_t references = 1;
    void *raw = nullptr;
    
    std::map<int32_t, event_info> events;
    int32_t magic = 0;
    std::string cls;
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

cq_obj *cq_retain_obj(cq_obj *obj) {
    if (obj == nullptr) {
        return nullptr;
    }
    
    cq_synchronize_obj(obj, {
        obj->references += 1;
    });
    
    return obj;
}

void cq_release_obj(cq_obj *obj) {
    if (obj == nullptr) {
        return;
    }
    
    cq_synchronize_obj(obj, {
        obj->references -= 1;
        
        if (obj->references <= 0) {
            obj->release(obj->raw);
            delete obj;
        }
    });
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

void cq_obj_listen_event(cq_obj *obj, int32_t event, cq_block block, void *data) {
    if (obj == nullptr) {
        return;
    }
    
    //NOTE: ignore that event is 0, 0 is reserved.
    if (event == 0 || !block) {
        return;
    }
    
    event_info info; {
        info.block = block;
        info.data = data;
    }
    obj->events[event] = info;
}

void cq_obj_send_event(cq_obj *obj, int32_t event) {
    if (!obj || event == 0) {
        return;
    }
    
    event_info info;
    if (cqMap::contains(obj->events, event)) {
        info = obj->events[event];
        cq_run_block(info.block, info.data);
    }
}
