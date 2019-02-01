#include "cbridgecore_p.h"

const CQType CQTypeNULL = {0LL};

CQType CQCreateBool(bool value) { return CQType(); }
CQType CQCreateInteger(int64_t value) { return CQType(); }
CQType CQCreateFloat(double value) { return CQType(); }
CQType CQCreateString(const char *value, int32_t length) { return CQType(); }

bool    CQGetBool  (CQType value) { return 0; }
int8_t  CQGetInt8  (CQType value) { return 0; }
int16_t CQGetInt16 (CQType value) { return 0; }
int32_t CQGetInt32 (CQType value) { return 0; }
int64_t CQGetInt64 (CQType value) { return 0; }
float   CQGetFloat (CQType value) { return 0; }
double  CQGetDouble(CQType value) { return 0; }

int32_t     CQGetStringLength(CQType value) { return 0; }
const char *CQGetStringValue (CQType value) { return 0; }

CQType  CQCreateArray  (void) { return CQType(); }
void    CQAddArrayItem (CQType array, CQType item0, CQType item1) {}
int32_t CQGetArraySize (CQType array) { return 0; }
CQType  CQGetArrayItem0(CQType array, int32_t position) { return CQType(); }
CQType  CQGetArrayItem1(CQType array, int32_t position) { return CQType(); }

void CQRetain (CQType value) {}
void CQRelease(CQType value) {}
