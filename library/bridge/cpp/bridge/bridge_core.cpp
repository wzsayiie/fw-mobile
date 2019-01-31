#include "bridge_core.h"

const BRGType BRGTypeNULL = {0LL};

BRGType BRGCreateBool(bool value) { return BRGType(); }
BRGType BRGCreateInteger(int64_t value) { return BRGType(); }
BRGType BRGCreateFloat(double value) { return BRGType(); }
BRGType BRGCreateString(const char *value, int32_t length) { return BRGType(); }

bool    BRGGetBool  (BRGType value) { return 0; }
int8_t  BRGGetInt8  (BRGType value) { return 0; }
int16_t BRGGetInt16 (BRGType value) { return 0; }
int32_t BRGGetInt32 (BRGType value) { return 0; }
int64_t BRGGetInt64 (BRGType value) { return 0; }
float   BRGGetFloat (BRGType value) { return 0; }
double  BRGGetDouble(BRGType value) { return 0; }

int32_t     BRGGetStringLength(BRGType value) { return 0; }
const char *BRGGetStringValue (BRGType value) { return 0; }

BRGType BRGCreateArray  (void) { return BRGType(); }
void    BRGAddArrayItem (BRGType array, BRGType item0, BRGType item1) {}
int32_t BRGGetArraySize (BRGType array) { return 0; }
BRGType BRGGetArrayItem0(BRGType array, int32_t position) { return BRGType(); }
BRGType BRGGetArrayItem1(BRGType array, int32_t position) { return BRGType(); }

void BRGRetain (BRGType value) {}
void BRGRelease(BRGType value) {}
