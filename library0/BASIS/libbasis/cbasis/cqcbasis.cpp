#include "cqcbasis.h"
#include "cqcppbasis.hh"
#include <cfloat>
#include <cmath>

//float number comparision.
bool cq_flt_equal(float  a, float  b) {return fabsf(a - b) < FLT_EPSILON;}
bool cq_dbl_equal(double a, double b) {return fabs (a - b) < DBL_EPSILON;}

//string:

bool cq_str_empty    (const char *s) {return s == nullptr || *s == '\0';}
bool cq_str_non_empty(const char *s) {return s != nullptr && *s != '\0';}

bool cq_u16str_empty    (const char16_t *s) {return s == nullptr || *s == '\0';}
bool cq_u16str_non_empty(const char16_t *s) {return s != nullptr && *s != '\0';}

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

//automatically allocate:

void *auto_alloc(int32_t size) {
    static int8_t begin[512];
    static int8_t *end = begin + sizeof(begin);
    static int8_t *cur = begin;
    
    if (size > sizeof(begin)) {
        return nullptr;
    }
    
    int8_t *ptr = nullptr;
    
    cq_synchronize({
        if (cur + size <= end) {
            ptr = cur;
        } else {
            ptr = begin;
        }
        cur = ptr + size;
    });
    
    memset(ptr, 0, size);
    
    return ptr;
}

//interfaces for multiplex structures:

template<class DST> void cq_x_clear(DST dst) {
    if (dst && dst->clear && dst->ref) {
        dst->clear(dst->ref);
    }
}

void cq_bytes_clear     (cq_bytes      *dst) { cq_x_clear(dst); }
void cq_int64_list_clear(cq_int64_list *dst) { cq_x_clear(dst); }
void cq_str_list_clear  (cq_str_list   *dst) { cq_x_clear(dst); }
void cq_ss_map_clear    (cq_ss_map     *dst) { cq_x_clear(dst); }

template<class DST, class SRC> void cq_x_append(DST dst, SRC src) {
    if (src && src->send && src->ref
     && dst && dst->recv && dst->ref)
    {
        src->send(src->ref, dst);
    }
}

void cq_bytes_append     (cq_bytes      *dst, cq_bytes      *src) { cq_x_append(dst, src); }
void cq_int64_list_append(cq_int64_list *dst, cq_int64_list *src) { cq_x_append(dst, src); }
void cq_str_list_append  (cq_str_list   *dst, cq_str_list   *src) { cq_x_append(dst, src); }
void cq_ss_map_append    (cq_ss_map     *dst, cq_ss_map     *src) { cq_x_append(dst, src); }

template<class DST, class SRC> void cq_x_assign(DST dst, SRC src) {
    cq_x_clear(dst);
    cq_x_append(dst, src);
}

void cq_bytes_assign     (cq_bytes      *dst, cq_bytes      *src) { cq_x_assign(dst, src); }
void cq_int64_list_assign(cq_int64_list *dst, cq_int64_list *src) { cq_x_assign(dst, src); }
void cq_str_list_assign  (cq_str_list   *dst, cq_str_list   *src) { cq_x_assign(dst, src); }
void cq_ss_map_assign    (cq_ss_map     *dst, cq_ss_map     *src) { cq_x_assign(dst, src); }

cq_bytes      *cq_cpp_x(std::vector<uint8_t>               &a) { return cq_cpp_bytes     (a); }
cq_int64_list *cq_cpp_x(std::vector<int64_t>               &a) { return cq_cpp_int64_list(a); }
cq_str_list   *cq_cpp_x(std::vector<std::string>           &a) { return cq_cpp_str_list  (a); }
cq_ss_map     *cq_cpp_x(std::map<std::string, std::string> &a) { return cq_cpp_ss_map    (a); }

template<class OBJ, class REF> REF cq_x_store(REF value) {
    static thread_local OBJ *storage = nullptr;
    if (storage == nullptr) {
        storage = new OBJ;
    }
    
    REF ref = cq_cpp_x(*storage);
    cq_x_assign(ref, value);
    return ref;
}

cq_bytes      *cq_bytes_store     (cq_bytes      *a) { return cq_x_store<std::vector<uint8_t              >>(a); }
cq_int64_list *cq_int64_list_store(cq_int64_list *a) { return cq_x_store<std::vector<int64_t              >>(a); }
cq_str_list   *cq_str_list_store  (cq_str_list   *a) { return cq_x_store<std::vector<std::string          >>(a); }
cq_ss_map     *cq_ss_map_store    (cq_ss_map     *a) { return cq_x_store<std::map<std::string, std::string>>(a); }

//object reference:

struct cq_ref_t {
    int32_t ref_count = 1;
    void *raw = nullptr;
    void (*del)(void *) = nullptr;
    
    virtual ~cq_ref_t();
};

cq_ref_t::~cq_ref_t() {
    if (del && raw) {
        del(raw);
    }
}

cq_ref *cq_retain(cq_ref *ref) {
    if (ref == nullptr) {
        return nullptr;
    }
    cq_synchronize_obj(ref, {
        auto ptr = (cq_ref_t *)ref;
        ptr->ref_count += 1;
    });
    return ref;
}

void cq_release(cq_ref *ref) {
    if (ref == nullptr) {
        return;
    }
    cq_synchronize_obj(ref, {
        auto ptr = (cq_ref_t *)ref;
        if (--ptr->ref_count <= 0) {
            delete ptr;
        }
    });
}

//block:

struct cq_block : cq_ref_t {
    void (*run)(void *raw) = nullptr;
};

cq_block *cq_block_retain(void *raw, void (*run)(void *raw), void (*del)(void *raw)) {
    if (!raw || !run) {
        return nullptr;
    }
    
    cq_block *block = new cq_block; {
        block->raw = raw;
        block->run = run;
        block->del = del;
    }
    return block;
}

void cq_block_run(cq_block *block) {
    if (block == nullptr) {
        return;
    }
    if (block->run && block->raw) {
        block->run(block->raw);
    }
}

//bridged object:

struct cq_object : cq_ref_t {
    std::map<int32_t, cq_block *> blocks;
    int32_t magic = 0;
    std::string cls;
    
    ~cq_object();
};

cq_object::~cq_object() {
    for (auto cp : blocks) {
        cq_release(cp.second);
    }
}

cq_object *cq_object_retain(void *raw, const char *cls, int32_t magic, void (*del)(void *raw)) {
    if (!raw || !del) {
        return nullptr;
    }
    
    cq_object *object = new cq_object; {
        object->raw   = raw;
        object->cls   = cqString::make(cls);
        object->magic = magic;
        object->del   = del;
    }
    return object;
}

void *cq_object_raw(cq_object *object) {
    if (object != nullptr) {
        return object->raw;
    }
    return nullptr;
}

const char *cq_object_cls(cq_object *object) {
    if (object != nullptr) {
        return object->cls.c_str();
    }
    return nullptr;
}

int32_t cq_object_magic(cq_object *object) {
    if (object != nullptr) {
        return object->magic;
    }
    return 0;
}

void cq_object_listen(cq_object *object, int32_t event, cq_block *block) {
    if (object == nullptr) {
        return;
    }
    
    //release old value.
    if (cqMap::contains(object->blocks, event)) {
        cq_block *old = object->blocks[event];
        cq_release(old);
        object->blocks.erase(event);
    }
    
    //retain new value.
    if (block != nullptr) {
        cq_retain(block);
        object->blocks[event] = block;
    }
}

void cq_object_emit(cq_object *object, int32_t event) {
    if (object == nullptr) {
        return;
    }
    if (cqMap::dontContain(object->blocks, event)) {
        return;
    }
    
    cq_block *block = object->blocks[event];
    cq_block_run(block);
}
