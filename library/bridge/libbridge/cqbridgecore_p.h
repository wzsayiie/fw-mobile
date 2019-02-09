#pragma once

#include <stdbool.h>
#include <stdint.h>

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

typedef struct CQType {
    union {
        int64_t handle;
        void *ptr;
    };
} CQType;

CQ_C_LINK const CQType CQTypeNULL;

CQ_C_LINK CQType CQCreateBool(bool value);
CQ_C_LINK CQType CQCreateInteger(int64_t value);
CQ_C_LINK CQType CQCreateFloat(double value);
CQ_C_LINK CQType CQCreateString(const char *value, int32_t length);

CQ_C_LINK bool    CQGetBool  (CQType value);
CQ_C_LINK int8_t  CQGetInt8  (CQType value);
CQ_C_LINK int16_t CQGetInt16 (CQType value);
CQ_C_LINK int32_t CQGetInt32 (CQType value);
CQ_C_LINK int64_t CQGetInt64 (CQType value);
CQ_C_LINK float   CQGetFloat (CQType value);
CQ_C_LINK double  CQGetDouble(CQType value);

CQ_C_LINK int32_t     CQGetStringLength(CQType value);
CQ_C_LINK const char *CQGetStringValue (CQType value);

CQ_C_LINK CQType  CQCreateArray  (void);
CQ_C_LINK void    CQAddArrayItem (CQType array, CQType item0, CQType item1);
CQ_C_LINK int32_t CQGetArraySize (CQType array);
CQ_C_LINK CQType  CQGetArrayItem0(CQType array, int32_t position);
CQ_C_LINK CQType  CQGetArrayItem1(CQType array, int32_t position);

CQ_C_LINK void CQRetain (CQType value);
CQ_C_LINK void CQRelease(CQType value);
