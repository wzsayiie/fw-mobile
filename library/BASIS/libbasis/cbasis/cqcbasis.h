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

//macro:

#define cq_array_count(arr) (sizeof(arr) / sizeof(*arr))

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

//storing values on current thread,
//until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_store_u8str(const char *string);
CQ_C_LINK const char16_t *cq_store_u16str(const char16_t *string);

//malloc pool:

struct _cq_malloc_pool {
    void *slots[64];
    int insert;
};

CQ_C_LINK void _cq_free_pool(struct _cq_malloc_pool *pool);

CQ_C_LINK void **_cq_push_u16str(struct _cq_malloc_pool *pool);
CQ_C_LINK void **_cq_push_u8str(struct _cq_malloc_pool *pool);
CQ_C_LINK void **_cq_push_array(struct _cq_malloc_pool *pool, size_t size, size_t count);

#ifndef __cplusplus

# if defined(__clang__)
#   define cq_malloc_pool __attribute((cleanup(_cq_free_pool))) struct _cq_malloc_pool __p = {NULL};
#   define cq_free_pool()
# elif defined(_MSC_VER)
#   define cq_malloc_pool struct _cq_malloc_pool __p = {NULL}; __try
#   define cq_free_pool() __finally {_cq_free_pool(&__p);}
# else
#   error "malloc pool is not supported for current compiler"
# endif

#define cq_push_u16str *_cq_push_u16str(&__p) = __p.slots[__p.insert] = (void *)
#define cq_push_u8str  *_cq_push_u8str (&__p) = __p.slots[__p.insert] = (void *)

#define cq_push_array(size, count) *_cq_push_array(&__p, size, count)

#endif

//unicode:

CQ_C_LINK const char16_t *cq_u16sfrom8s(const char *src);
CQ_C_LINK const char *cq_u8sfrom16s(const char16_t *src);
