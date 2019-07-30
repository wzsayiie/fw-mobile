#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// +-------------+ +-------+
// |     mac     | |android|
// | +---+ +---+ | +-------+
// | |ios| |osx| | +-------+
// | +---+ +---+ | |windows|
// +-------------+ +-------+

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

//mac don't provide "uchar.h"
#ifndef __cplusplus
typedef uint16_t char16_t;
#endif

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

//data:

struct _cq_data {
    void   *items;  //ends with '\0' as the last item
    int32_t size ;  //size of every item
    int32_t count;  //item count, don't contain the last item('\0')
};

CQ_C_LINK void _cq_assign_data(struct _cq_data *data, const void *items, int32_t size, int32_t count);
CQ_C_LINK void _cq_clear_data(struct _cq_data *data);
CQ_C_LINK void _cq_resize_data(struct _cq_data *data, int32_t size, int32_t count);

//string:

CQ_C_LINK bool cq_u8str_empty(const char *string);
CQ_C_LINK bool cq_u16str_empty(const char16_t *string);

//the return value needed to free().
CQ_C_LINK char *cq_copy_u8str(const char *string);
CQ_C_LINK char16_t *cq_copy_u16str(const char16_t *string);

//storing values on current thread, until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_store_u8str(const char *string);
CQ_C_LINK const char16_t *cq_store_u16str(const char16_t *string);

//unicode:

CQ_C_LINK const char16_t *cq_u16sfrom8s(const char *src);
CQ_C_LINK const char *cq_u8sfrom16s(const char16_t *src);
