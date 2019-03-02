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
} CQBridgeValue;

#ifdef __cplusplus
inline CQBridgeValue CQBridgeValueMake(int64_t h) { CQBridgeValue v = {(int64_t)h}; return v; }
inline CQBridgeValue CQBridgeValueMake(void   *p) { CQBridgeValue v = {(int64_t)p}; return v; }
#endif

static const CQBridgeValue CQBridgeValueNull = {0};

typedef int32_t CQBridgeType;

CQ_C_LINK const CQBridgeType CQBridgeTypeNull  ;
CQ_C_LINK const CQBridgeType CQBridgeTypeBool  ;
CQ_C_LINK const CQBridgeType CQBridgeTypeInt8  ;
CQ_C_LINK const CQBridgeType CQBridgeTypeInt16 ;
CQ_C_LINK const CQBridgeType CQBridgeTypeInt32 ;
CQ_C_LINK const CQBridgeType CQBridgeTypeInt64 ;
CQ_C_LINK const CQBridgeType CQBridgeTypeFloat ;
CQ_C_LINK const CQBridgeType CQBridgeTypeDouble;
CQ_C_LINK const CQBridgeType CQBridgeTypeString;
CQ_C_LINK const CQBridgeType CQBridgeTypeTable ;

CQ_C_LINK CQBridgeType CQBridgeCheckType(CQBridgeValue value);

CQ_C_LINK CQBridgeValue CQBridgeCreateBool  (bool    raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateInt8  (int8_t  raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateInt16 (int16_t raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateInt32 (int32_t raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateInt64 (int64_t raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateFloat (float   raw);
CQ_C_LINK CQBridgeValue CQBridgeCreateDouble(double  raw);

CQ_C_LINK bool    CQBridgeGetBool  (CQBridgeValue value);
CQ_C_LINK int8_t  CQBridgeGetInt8  (CQBridgeValue value);
CQ_C_LINK int16_t CQBridgeGetInt16 (CQBridgeValue value);
CQ_C_LINK int32_t CQBridgeGetInt32 (CQBridgeValue value);
CQ_C_LINK int64_t CQBridgeGetInt64 (CQBridgeValue value);
CQ_C_LINK float   CQBridgeGetFloat (CQBridgeValue value);
CQ_C_LINK double  CQBridgeGetDouble(CQBridgeValue value);

CQ_C_LINK CQBridgeValue CQBridgeCreateString(const char *raw, int32_t len);
CQ_C_LINK int32_t       CQBridgeStringLength(CQBridgeValue value);
CQ_C_LINK const char   *CQBridgeStringValue (CQBridgeValue value);

CQ_C_LINK CQBridgeValue CQBridgeCreateTable  (void);
CQ_C_LINK void          CQBridgeTableAdd     (CQBridgeValue table, CQBridgeValue key, CQBridgeValue value);
CQ_C_LINK int32_t       CQBridgeTableSize    (CQBridgeValue table);
CQ_C_LINK CQBridgeValue CQBridgeTableGetKey  (CQBridgeValue table, int32_t position);
CQ_C_LINK CQBridgeValue CQBridgeTableGetValue(CQBridgeValue table, int32_t position);

CQ_C_LINK void CQBridgeRetain (CQBridgeValue value);
CQ_C_LINK void CQBridgeRelease(CQBridgeValue value);
