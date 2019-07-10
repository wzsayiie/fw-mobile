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

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

struct _cq_data {
    void *bytes;    //ends with '\0'
    int32_t size;   //don't contain '\0' of the end
};

CQ_C_LINK void _cq_assign_data(struct _cq_data *data, const void *bytes, int32_t size);
CQ_C_LINK void _cq_clear_data(struct _cq_data *data);

//NOTE: reserve additional '\0' at the end, but don't set bytes zero.
CQ_C_LINK void _cq_resize_data(struct _cq_data *data, int32_t size);

CQ_C_LINK bool cq_string_empty(const char *string);

//storing bytes on current thread,
//until call of cq_store_xx again on same thread.
CQ_C_LINK const char *cq_store_string(const char *value);
CQ_C_LINK const void *cq_store_bytes(const void *bytes, int32_t size);

//return value ends with '\0'.
CQ_C_LINK const char *cq_stored_string(void);
CQ_C_LINK const void *cq_stored_bytes(void);

//the size do not contain '\0' of the end.
CQ_C_LINK int32_t cq_stored_size(void);
