#pragma once

#include <stdbool.h>
#include <stdint.h>

# ifdef __cplusplus
#   define BRG_EXPORT extern "C"
# else
#   define BRG_EXPORT
# endif

typedef struct BRGType {
    union {
        int64_t handle;
        void *ptr;
    };
} BRGType;

BRG_EXPORT BRGType BRGCreateBool(bool value);
BRG_EXPORT BRGType BRGCreateInteger(int64_t value);
BRG_EXPORT BRGType BRGCreateFloat(double value);
BRG_EXPORT BRGType BRGCreateString(const char *value, int32_t length);

BRG_EXPORT bool    BRGGetBool  (BRGType value);
BRG_EXPORT int8_t  BRGGetInt8  (BRGType value);
BRG_EXPORT int16_t BRGGetInt16 (BRGType value);
BRG_EXPORT int32_t BRGGetInt32 (BRGType value);
BRG_EXPORT int64_t BRGGetInt64 (BRGType value);
BRG_EXPORT float   BRGGetFloat (BRGType value);
BRG_EXPORT double  BRGGetDouble(BRGType value);

BRG_EXPORT int32_t     BRGGetStringLength(BRGType value);
BRG_EXPORT const char *BRGGetStringValue (BRGType value);

BRG_EXPORT BRGType BRGCreateArray  (void);
BRG_EXPORT void    BRGAddArrayItem (BRGType array, BRGType item0, BRGType item1);
BRG_EXPORT int32_t BRGGetArraySize (BRGType array);
BRG_EXPORT BRGType BRGGetArrayItem0(BRGType array, int32_t position);
BRG_EXPORT BRGType BRGGetArrayItem1(BRGType array, int32_t position);

BRG_EXPORT void BRGRetain (BRGType value);
BRG_EXPORT void BRGRelease(BRGType value);
