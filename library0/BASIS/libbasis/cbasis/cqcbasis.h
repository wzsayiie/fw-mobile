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

typedef void (*cq_bool_out  )(bool    value);
typedef void (*cq_int8_out  )(int8_t  value);
typedef void (*cq_int16_out )(int16_t value);
typedef void (*cq_int32_out )(int32_t value);
typedef void (*cq_int64_out )(int64_t value);
typedef void (*cq_float_out )(float   value);
typedef void (*cq_double_out)(double  value);

typedef void (*cq_str_out     )(const char *str);
typedef void (*cq_bytes_out   )(const void *ptr, int32_t len);
typedef void (*cq_i64_list_out)(int64_t     val);
typedef void (*cq_str_list_out)(const char *val);
typedef void (*cq_ss_map_out  )(const char *key, const char *val);

typedef void (*cq_bool_in  )(cq_bool_out   out);
typedef void (*cq_int8_in  )(cq_int8_out   out);
typedef void (*cq_int16_in )(cq_int16_out  out);
typedef void (*cq_int32_in )(cq_int32_out  out);
typedef void (*cq_int64_in )(cq_int64_out  out);
typedef void (*cq_float_in )(cq_float_out  out);
typedef void (*cq_double_in)(cq_double_out out);

typedef void (*cq_str_in     )(cq_str_out      out);
typedef void (*cq_bytes_in   )(cq_bytes_out    out);
typedef void (*cq_i64_list_in)(cq_i64_list_out out);
typedef void (*cq_str_list_in)(cq_str_list_out out);
typedef void (*cq_ss_map_in  )(cq_ss_map_out   out);

//block:

cq_enum(int32_t, cq_type) {
    
    CQ_TYPE_NULL = 0,
    
    CQ_TYPE_BOOL     = 0x11,
    CQ_TYPE_INT8     = 0x12, CQ_TYPE_INT16  = 0x13,
    CQ_TYPE_INT32    = 0x14, CQ_TYPE_INT64  = 0x15,
    CQ_TYPE_FLOAT    = 0x16, CQ_TYPE_DOUBLE = 0x17,
    CQ_TYPE_STR      = 0x18,
    CQ_TYPE_BYTES    = 0x19,
    CQ_TYPE_I64_LIST = 0x1A,
    CQ_TYPE_STR_LIST = 0x1B,
    CQ_TYPE_SS_MAP   = 0x1C,
    
    CQ_TYPE_BOOL_IN     = 0x21,
    CQ_TYPE_INT8_IN     = 0x22, CQ_TYPE_INT16_IN  = 0x23,
    CQ_TYPE_INT32_IN    = 0x24, CQ_TYPE_INT64_IN  = 0x25,
    CQ_TYPE_FLOAT_IN    = 0x26, CQ_TYPE_DOUBLE_IN = 0x27,
    CQ_TYPE_STR_IN      = 0x28,
    CQ_TYPE_BYTES_IN    = 0x29,
    CQ_TYPE_I64_LIST_IN = 0x2A,
    CQ_TYPE_STR_LIST_IN = 0x2B,
    CQ_TYPE_SS_MAP_IN   = 0x2C,
    
    CQ_TYPE_BOOL_OUT     = 0x31,
    CQ_TYPE_INT8_OUT     = 0x32, CQ_TYPE_INT16_OUT  = 0x33,
    CQ_TYPE_INT32_OUT    = 0x34, CQ_TYPE_INT64_OUT  = 0x35,
    CQ_TYPE_FLOAT_OUT    = 0x36, CQ_TYPE_DOUBLE_OUT = 0x37,
    CQ_TYPE_STR_OUT      = 0x38,
    CQ_TYPE_BYTES_OUT    = 0x39,
    CQ_TYPE_I64_LIST_OUT = 0x3A,
    CQ_TYPE_STR_LIST_OUT = 0x3B,
    CQ_TYPE_SS_MAP_OUT   = 0x3C,
};

//$data is user defined parameters.
typedef void (*cq_block)(void *data);

//before calling cq_run_block(), using cq_set_block_param() to assign block parameters.
//when the cq_block is being called, it can use cq_block_param() to get these values.

CQ_C_LINK void cq_set_block_param(const char *name, cq_type type, void *value);
CQ_C_LINK void *cq_block_param(const char *name, cq_type type);

CQ_C_LINK void cq_run_block(cq_block block, void *data);

//object reference:

typedef void cq_obj;

CQ_C_LINK cq_obj *cq_obj_retain_raw(void *raw, void (*release)(void *raw));

//cq_obj_retain() and cq_obj_relase() is thread safe.
CQ_C_LINK cq_obj *cq_obj_retain (cq_obj *obj);
CQ_C_LINK void    cq_obj_release(cq_obj *obj);

CQ_C_LINK void       *cq_obj_raw      (cq_obj *obj);
CQ_C_LINK void        cq_obj_set_cls  (cq_obj *obj, const char *cls);
CQ_C_LINK const char *cq_obj_cls      (cq_obj *obj);
CQ_C_LINK void        cq_obj_set_magic(cq_obj *obj, int32_t magic);
CQ_C_LINK int32_t     cq_obj_magic    (cq_obj *obj);

CQ_C_LINK void cq_obj_listen_event(cq_obj *obj, int32_t event, cq_block func, void *data);
CQ_C_LINK void cq_obj_emit_event  (cq_obj *obj, int32_t event);
