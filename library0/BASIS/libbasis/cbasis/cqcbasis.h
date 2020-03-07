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

CQ_C_LINK bool cq_str_empty(const char *string);
CQ_C_LINK bool cq_u16str_empty(const char16_t *string);

//storing values on current thread, until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_store_str(const char *string);
CQ_C_LINK const char16_t *cq_store_u16str(const char16_t *string);

//unicode:

//char8_t is a new type since c++20.
//this typedef wants that char and _char8_t is same type, to avoid type conversion.
//
//NOTE:
//char8_t form c++20 is unsigned. whether char is signed or unsigned is configurable.
//CLANG use argument '-funsigned-char' to specify char unsigned;
//MS CL use argument '/J' to specify char unsigned.
typedef char _char8_t;

CQ_C_LINK const char16_t *cq_u16s_from8s(const _char8_t *src);
CQ_C_LINK const _char8_t *cq_u8s_from16s(const char16_t *src);

//runnable.
typedef void (*cq_runnable)(void *);

//to define a struct.
#define cq_struct(NAME) typedef struct NAME NAME; struct NAME

//interfaces for multiplex structures:

typedef void (*cq_bytes_out   )(const void *bytes, int32_t len);
typedef void (*cq_int_list_out)(int64_t item);
typedef void (*cq_str_list_out)(const char *item);
typedef void (*cq_ss_map_out  )(const char *key, const char *value);

typedef void (*cq_bytes_in   )(cq_bytes_out    out);
typedef void (*cq_int_list_in)(cq_int_list_out out);
typedef void (*cq_str_list_in)(cq_str_list_out out);
typedef void (*cq_ss_map_in  )(cq_ss_map_out   out);

//object reference:

cq_struct(cq_obj);

CQ_C_LINK cq_obj *cq_retain_raw_obj(void *raw, void (*release)(void *raw));

//cq_retain_obj() and cq_relase_obj() is thread safe.
CQ_C_LINK cq_obj *cq_retain_obj(cq_obj *obj);
CQ_C_LINK void cq_release_obj(cq_obj *obj);

CQ_C_LINK void *cq_obj_raw(cq_obj *obj);

CQ_C_LINK void cq_set_obj_cls(cq_obj *obj, const char *cls);
CQ_C_LINK const char *cq_obj_cls(cq_obj *obj);

CQ_C_LINK void cq_set_obj_magic(cq_obj *obj, int32_t magic);
CQ_C_LINK int32_t cq_obj_magic(cq_obj *obj);
