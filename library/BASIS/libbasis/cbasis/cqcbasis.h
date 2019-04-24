#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

# ifdef __APPLE__
#   include <TargetConditionals.h>
# endif

# if ANDROID
#   define CQ_ON_ANDROID 1
#   define CQ_ON_IPHONE  0
#   define CQ_ON_OSX     0
#   define CQ_ON_WINDOWS 0
# elif TARGET_OS_IPHONE
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IPHONE  1
#   define CQ_ON_OSX     0
#   define CQ_ON_WINDOWS 0
# elif TARGET_OS_OSX
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IPHONE  0
#   define CQ_ON_OSX     1
#   define CQ_ON_WINDOWS 0
# elif _WIN32
#   define CQ_ON_ANDROID 0
#   define CQ_ON_IPHONE  0
#   define CQ_ON_OSX     0
#   define CQ_ON_WINDOWS 1
# endif

extern const bool cq_on_android;
extern const bool cq_on_iphone ;
extern const bool cq_on_osx    ;
extern const bool cq_on_windows;

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

typedef const char *PCSTR;

//storing a string on current thread,
//until call of cq_string_store_xx again on same thread.
CQ_C_LINK const char *cq_string_store_string(const char *value);
CQ_C_LINK const char *cq_string_store_bytes(const char *bytes, int32_t size);

//return value ends with '\0'.
CQ_C_LINK const char *cq_string_get_stored_string(void);

//the size do not contain '\0' of the end.
CQ_C_LINK int32_t cq_string_get_stored_size(void);
