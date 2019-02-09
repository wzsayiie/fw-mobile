#pragma once

#include <stdbool.h>
#include <stdint.h>

# ifdef __cplusplus
#   define CQ_EXPORT extern "C"
# else
#   define CQ_EXPORT
# endif

typedef struct CQType {
    union {
        int64_t handle;
        void *ptr;
    };
} CQType;

CQ_EXPORT const CQType CQTypeNULL;

CQ_EXPORT CQType CQCreateBool(bool value);
CQ_EXPORT CQType CQCreateInteger(int64_t value);
CQ_EXPORT CQType CQCreateFloat(double value);
CQ_EXPORT CQType CQCreateString(const char *value, int32_t length);

CQ_EXPORT bool    CQGetBool  (CQType value);
CQ_EXPORT int8_t  CQGetInt8  (CQType value);
CQ_EXPORT int16_t CQGetInt16 (CQType value);
CQ_EXPORT int32_t CQGetInt32 (CQType value);
CQ_EXPORT int64_t CQGetInt64 (CQType value);
CQ_EXPORT float   CQGetFloat (CQType value);
CQ_EXPORT double  CQGetDouble(CQType value);

CQ_EXPORT int32_t     CQGetStringLength(CQType value);
CQ_EXPORT const char *CQGetStringValue (CQType value);

CQ_EXPORT CQType  CQCreateArray  (void);
CQ_EXPORT void    CQAddArrayItem (CQType array, CQType item0, CQType item1);
CQ_EXPORT int32_t CQGetArraySize (CQType array);
CQ_EXPORT CQType  CQGetArrayItem0(CQType array, int32_t position);
CQ_EXPORT CQType  CQGetArrayItem1(CQType array, int32_t position);

CQ_EXPORT void CQRetain (CQType value);
CQ_EXPORT void CQRelease(CQType value);
