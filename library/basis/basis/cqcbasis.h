#pragma once

# ifdef _MSC_VER
#   define _CRT_SECURE_NO_WARNINGS
# endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// +-------------+ +-----------------+ +-------+
// |     mac     | |     windows     | |       |
// | +---+ +---+ | | +-----+ +-----+ | |       |
// | |ios| |osx| | | |win32| |winrt| | |android|
// | +---+ +---+ | | +-----+ +-----+ | |       |
// +-------------+ +-----------------+ +-------+

# ifdef __APPLE__
#   include <TargetConditionals.h>
# endif

# if ANDROID
#   define CQ_ON_ANDROID 1
#   define CQ_ON_IOS     0
#   define CQ_ON_WINDOWS 0
#   define CQ_ON_OSX     0
# elif TARGET_OS_IOS
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IOS     1
#   define CQ_ON_WINDOWS 0
#   define CQ_ON_OSX     0
# elif _WIN32
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IOS     0
#   define CQ_ON_WINDOWS 1
#   define CQ_ON_OSX     0
# elif TARGET_OS_OSX
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IOS     0
#   define CQ_ON_WINDOWS 0
#   define CQ_ON_OSX     1
# else
#   error "unknown os"
# endif

# if CQ_ON_ANDROID
#   define CQ_IF_ON_ANDROID(CODE) CODE
#   define CQ_IF_ON_IOS(    CODE)
#   define CQ_IF_ON_WINDOWS(CODE)
#   define CQ_IF_ON_OSX(    CODE)
# elif CQ_ON_IOS
#   define CQ_IF_ON_ANDROID(CODE)
#   define CQ_IF_ON_IOS(    CODE) CODE
#   define CQ_IF_ON_WINDOWS(CODE)
#   define CQ_IF_ON_OSX(    CODE)
# elif CQ_ON_WINDOWS
#   define CQ_IF_ON_ANDROID(CODE)
#   define CQ_IF_ON_IOS(    CODE)
#   define CQ_IF_ON_WINDOWS(CODE) CODE
#   define CQ_IF_ON_OSX(    CODE)
# elif CQ_ON_OSX
#   define CQ_IF_ON_ANDROID(CODE)
#   define CQ_IF_ON_IOS(    CODE)
#   define CQ_IF_ON_WINDOWS(CODE)
#   define CQ_IF_ON_OSX(    CODE) CODE
# endif

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

//float number comparision.
CQ_C_LINK bool cq_flt_equal(float  a, float  b);
CQ_C_LINK bool cq_dbl_equal(double a, double b);

//string:

//mac don't provide "uchar.h"
#ifndef __cplusplus
typedef uint16_t char16_t;
#endif

//if $str == null or strlen($str) == 0, the $str is regarded as "empty".
CQ_C_LINK bool cq_str_empty(const char *str);
CQ_C_LINK bool cq_str_non_empty(const char *str);
CQ_C_LINK bool cq_u16str_empty(const char16_t *str);
CQ_C_LINK bool cq_u16str_non_empty(const char16_t *str);

//storing values on current thread, until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_str_store(const char *str);
CQ_C_LINK const char16_t *cq_u16str_store(const char16_t *str);

//unicode coding conversion.
CQ_C_LINK const char16_t *cq_u16s_from_u8s(const char *src);
CQ_C_LINK const char *cq_u8s_from_u16s(const char16_t *src);

//define user structures:

#define cq_struct(NAME)\
/**/    typedef struct NAME NAME;\
/**/    struct NAME

#define cq_enum(TYPE, NAME)\
/**/    typedef TYPE NAME;\
/**/    enum

//allocating a small memory block(that will be assigned 0) from a recycled block.
//$size should be a relatively small value, and the return value does not need to be released.
CQ_C_LINK void *auto_alloc(int32_t size);

//interfaces for multiplex structures:

cq_struct(cq_bytes) {
    void (*clear)(void *ref);
    void (*recv )(void *ref, const void *bytes, int32_t length);
    void (*send )(void *ref, cq_bytes *dst);
    void *ref;
};

cq_struct(cq_int64_list) {
    void (*clear)(void *ref);
    void (*recv )(void *ref, int64_t item);
    void (*send )(void *ref, cq_int64_list *dst);
    void *ref;
};

cq_struct(cq_str_list) {
    void (*clear)(void *ref);
    void (*recv )(void *ref, const char *item);
    void (*send )(void *ref, cq_str_list *dst);
    void *ref;
};

cq_struct(cq_ss_map) {
    void (*clear)(void *ref);
    void (*recv )(void *ref, const char *key, const char *value);
    void (*send )(void *ref, cq_ss_map *dst);
    void *ref;
};

CQ_C_LINK void cq_bytes_clear     (cq_bytes      *dst);
CQ_C_LINK void cq_int64_list_clear(cq_int64_list *dst);
CQ_C_LINK void cq_str_list_clear  (cq_str_list   *dst);
CQ_C_LINK void cq_ss_map_clear    (cq_ss_map     *dst);

CQ_C_LINK void cq_bytes_append     (cq_bytes      *dst, cq_bytes      *src);
CQ_C_LINK void cq_int64_list_append(cq_int64_list *dst, cq_int64_list *src);
CQ_C_LINK void cq_str_list_append  (cq_str_list   *dst, cq_str_list   *src);
CQ_C_LINK void cq_ss_map_append    (cq_ss_map     *dst, cq_ss_map     *src);

CQ_C_LINK void cq_bytes_assign     (cq_bytes      *dst, cq_bytes      *src);
CQ_C_LINK void cq_int64_list_assign(cq_int64_list *dst, cq_int64_list *src);
CQ_C_LINK void cq_str_list_assign  (cq_str_list   *dst, cq_str_list   *src);
CQ_C_LINK void cq_ss_map_assign    (cq_ss_map     *dst, cq_ss_map     *src);

//storing the data on current thread,
//until call of cq_store_xx again on same thread.
CQ_C_LINK cq_bytes      *cq_bytes_store     (cq_bytes      *value);
CQ_C_LINK cq_int64_list *cq_int64_list_store(cq_int64_list *value);
CQ_C_LINK cq_str_list   *cq_str_list_store  (cq_str_list   *value);
CQ_C_LINK cq_ss_map     *cq_ss_map_store    (cq_ss_map     *value);

//object reference:

typedef void cq_ref;

//cq_retain() and cq_relase() is thread safe.
CQ_C_LINK cq_ref *cq_retain(cq_ref *ref);
CQ_C_LINK void cq_release(cq_ref *ref);

//block:

cq_struct(cq_block);

CQ_C_LINK cq_block *cq_block_retain(void *raw, void (*run)(void *raw), void (*del)(void *raw));
CQ_C_LINK void cq_block_run(cq_block *block);

//bridged object:

cq_struct(cq_object);

CQ_C_LINK cq_object *cq_object_retain(void *raw, const char *cls, int32_t magic, void (*del)(void *raw));

CQ_C_LINK void       *cq_object_raw  (cq_object *object);
CQ_C_LINK const char *cq_object_cls  (cq_object *object);
CQ_C_LINK int32_t     cq_object_magic(cq_object *object);

CQ_C_LINK void cq_object_listen(cq_object *object, int32_t event, cq_block *block);
CQ_C_LINK void cq_object_emit  (cq_object *object, int32_t event);

#define cq_def_object(N)\
/**/    cq_struct(N);\
/**/    static inline void N##_listen (N *a, int32_t e, cq_block *b) {return cq_object_listen((cq_object *)a, e, b);}\
/**/    static inline void N##_emit   (N *a, int32_t e             ) {return cq_object_emit  ((cq_object *)a, e   );}
