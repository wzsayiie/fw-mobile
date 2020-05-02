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

//if $str == null or strlen($str) == 0, return true.
CQ_C_LINK bool cq_str_empty(const char *str);
CQ_C_LINK bool cq_u16str_empty(const char16_t *str);

//storing values on current thread, until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_store_str(const char *str);
CQ_C_LINK const char16_t *cq_store_u16str(const char16_t *str);

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

//interfaces for multiplex structures:

typedef void (*cq_bytes_out   )(const void *ptr, int32_t len);
typedef void (*cq_i64_list_out)(int64_t     val);
typedef void (*cq_str_list_out)(const char *val);
typedef void (*cq_ss_map_out  )(const char *key, const char *val);

typedef void (*cq_bytes_in   )(cq_bytes_out    out);
typedef void (*cq_i64_list_in)(cq_i64_list_out out);
typedef void (*cq_str_list_in)(cq_str_list_out out);
typedef void (*cq_ss_map_in  )(cq_ss_map_out   out);

//object reference:

cq_struct(cq_obj);

//cq_obj_retain() and cq_obj_relase() is thread safe.
CQ_C_LINK cq_obj *cq_obj_retain(cq_obj *obj);
CQ_C_LINK void cq_obj_release(cq_obj *obj);

//block:

cq_struct(cq_block);

CQ_C_LINK cq_block *cq_block_retain_raw(void *raw, void (*run)(void *raw), void (*del)(void *raw));
CQ_C_LINK cq_block *cq_block_retain(cq_block *block);
CQ_C_LINK void cq_block_release(cq_block *block);
CQ_C_LINK void cq_block_run(cq_block *block);

//bridged object:

cq_struct(cq_bridge);

CQ_C_LINK cq_bridge *cq_bridge_retain_raw(void *raw, const char *cls, int32_t magic, void (*del)(void *raw));
CQ_C_LINK cq_bridge *cq_bridge_retain(cq_bridge *bridge);
CQ_C_LINK void cq_bridge_release(cq_bridge *bridge);

CQ_C_LINK void       *cq_bridge_raw  (cq_bridge *bridge);
CQ_C_LINK const char *cq_bridge_cls  (cq_bridge *bridge);
CQ_C_LINK int32_t     cq_bridge_magic(cq_bridge *bridge);

CQ_C_LINK void cq_bridge_listen(cq_bridge *bridge, int32_t event, cq_block *block);
CQ_C_LINK void cq_bridge_emit  (cq_bridge *bridge, int32_t event);

#define cq_bridged_struct(N)\
/**/    cq_struct(N);\
/**/    static inline N *  N##_retain (N *a                        ) {return (N *)cq_bridge_retain ((cq_bridge *)a      );}\
/**/    static inline void N##_release(N *a                        ) {return      cq_bridge_release((cq_bridge *)a      );}\
/**/    static inline void N##_listen (N *a, int32_t e, cq_block *b) {return      cq_bridge_listen ((cq_bridge *)a, e, b);}\
/**/    static inline void N##_emit   (N *a, int32_t e             ) {return      cq_bridge_emit   ((cq_bridge *)a, e   );}
