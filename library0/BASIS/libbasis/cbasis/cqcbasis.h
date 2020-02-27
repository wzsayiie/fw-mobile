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

//runable:

typedef void (*cq_runnable)(void *);

//multiplex structures:

typedef struct cq_bytes   cq_bytes  ;
typedef struct cq_int64s  cq_int64s ;
typedef struct cq_strings cq_strings;
typedef struct cq_ss_map  cq_ss_map ;

typedef void (*cq_bytes_receiver  )(cq_bytes   *dst, const void *ptr, int32_t len);
typedef void (*cq_int64s_receiver )(cq_int64s  *dst, int64_t     val);
typedef void (*cq_strings_receiver)(cq_strings *dst, const char *val);
typedef void (*cq_ss_map_receiver )(cq_ss_map  *dst, const char *key, const char *val);

typedef void (*cq_bytes_sender  )(cq_bytes   *src, cq_bytes_receiver   recv, cq_bytes   *dst);
typedef void (*cq_int64s_sender )(cq_int64s  *src, cq_int64s_receiver  recv, cq_int64s  *dst);
typedef void (*cq_strings_sender)(cq_strings *src, cq_strings_receiver recv, cq_strings *dst);
typedef void (*cq_ss_map_sender )(cq_ss_map  *src, cq_ss_map_receiver  recv, cq_ss_map  *dst);

CQ_C_LINK void cq_c_bytes_receiver  (cq_bytes   *dst, const void *ptr, int32_t len);
CQ_C_LINK void cq_c_int64s_receiver (cq_int64s  *dst, int64_t     val);
CQ_C_LINK void cq_c_strings_receiver(cq_strings *dst, const char *val);
CQ_C_LINK void cq_c_ss_map_receiver (cq_ss_map  *dst, const char *key, const char *val);

CQ_C_LINK void cq_c_bytes_sender  (cq_bytes   *src, cq_bytes_receiver   recv, cq_bytes   *dst);
CQ_C_LINK void cq_c_int64s_sender (cq_int64s  *src, cq_int64s_receiver  recv, cq_int64s  *dst);
CQ_C_LINK void cq_c_strings_sender(cq_strings *src, cq_strings_receiver recv, cq_strings *dst);
CQ_C_LINK void cq_c_ss_map_sender (cq_ss_map  *src, cq_ss_map_receiver  recv, cq_ss_map  *dst);

CQ_C_LINK cq_bytes   *cq_store_c_bytes  (cq_bytes_sender   send, cq_bytes   *src);
CQ_C_LINK cq_int64s  *cq_store_c_int64s (cq_int64s_sender  send, cq_int64s  *src);
CQ_C_LINK cq_strings *cq_store_c_strings(cq_strings_sender send, cq_strings *src);
CQ_C_LINK cq_ss_map  *cq_store_c_ss_map (cq_ss_map_sender  send, cq_ss_map  *src);
