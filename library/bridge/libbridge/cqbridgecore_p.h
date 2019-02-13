#pragma once

#include <stdbool.h>
#include <stdint.h>

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

typedef struct {
    int64_t handle;
} CQValue;

#ifdef __cplusplus
static inline CQValue CQValueMake(int64_t h) { CQValue v = {(int64_t)h}; return v; }
static inline CQValue CQValueMake(void   *p) { CQValue v = {(int64_t)p}; return v; }
#endif

static const CQValue CQValueNull = {0};

typedef int32_t CQType;

CQ_C_LINK const CQType CQTypeNull  ;
CQ_C_LINK const CQType CQTypeBool  ;
CQ_C_LINK const CQType CQTypeInt8  ;
CQ_C_LINK const CQType CQTypeInt16 ;
CQ_C_LINK const CQType CQTypeInt32 ;
CQ_C_LINK const CQType CQTypeInt64 ;
CQ_C_LINK const CQType CQTypeFloat ;
CQ_C_LINK const CQType CQTypeDouble;
CQ_C_LINK const CQType CQTypeString;
CQ_C_LINK const CQType CQTypeTable ;

CQ_C_LINK CQType CQCheckType(CQValue value);

CQ_C_LINK CQValue CQCreateBool  (bool    raw);
CQ_C_LINK CQValue CQCreateInt8  (int8_t  raw);
CQ_C_LINK CQValue CQCreateInt16 (int16_t raw);
CQ_C_LINK CQValue CQCreateInt32 (int32_t raw);
CQ_C_LINK CQValue CQCreateInt64 (int64_t raw);
CQ_C_LINK CQValue CQCreateFloat (float   raw);
CQ_C_LINK CQValue CQCreateDouble(double  raw);

CQ_C_LINK bool    CQGetBool  (CQValue value);
CQ_C_LINK int8_t  CQGetInt8  (CQValue value);
CQ_C_LINK int16_t CQGetInt16 (CQValue value);
CQ_C_LINK int32_t CQGetInt32 (CQValue value);
CQ_C_LINK int64_t CQGetInt64 (CQValue value);
CQ_C_LINK float   CQGetFloat (CQValue value);
CQ_C_LINK double  CQGetDouble(CQValue value);

CQ_C_LINK CQValue     CQCreateString   (const char *raw, int32_t len);
CQ_C_LINK int32_t     CQGetStringLength(CQValue value);
CQ_C_LINK const char *CQGetStringValue (CQValue value);

CQ_C_LINK CQValue CQCreateTable  (void);
CQ_C_LINK void    CQAddTableItem (CQValue table, CQValue item0, CQValue item1);
CQ_C_LINK int32_t CQGetTableSize (CQValue table);
CQ_C_LINK CQValue CQGetTableItem0(CQValue table, int32_t position);
CQ_C_LINK CQValue CQGetTableItem1(CQValue table, int32_t position);

CQ_C_LINK void CQRetain (CQValue value);
CQ_C_LINK void CQRelease(CQValue value);
