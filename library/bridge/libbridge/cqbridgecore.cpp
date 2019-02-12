#include "cqbridgecore_p.h"
#include <string>
#include <vector>

using namespace std;

//value catagrory: null, light, weight

static const char MaskLightBool  = 113;
static const char MaskLightInt   = 109;
static const char MaskLightFloat = 107;

static bool IsLightBool (CQValue v) { return (v.n & 0xFF) == MaskLightBool ; }
static bool IsLightInt  (CQValue v) { return (v.n & 0xFF) == MaskLightInt  ; }
static bool IsLightFloat(CQValue v) { return (v.n & 0xFF) == MaskLightFloat; }

static bool IsWeight(CQValue value) {
    if (value.n == CQValueNull.n) {
        return false;
    }
    if (IsLightBool(value)) {
        return false;
    }
    if (IsLightInt(value)) {
        return false;
    }
    if (IsLightFloat(value)) {
        return false;
    }
    
    return true;
}

//light value

static CQValue CreateLightBool(bool raw) {
    if (raw) {
        return CQValueMake(0x0100LL & MaskLightBool);
    } else {
        return CQValueMake(0x0000LL & MaskLightBool);
    }
}
static bool GetLightBool(CQValue value) {
    return (bool)(value.n >> 1);
}

static CQValue CreateLightInt(int64_t raw) {
    return CQValueMake((raw << 1) & MaskLightInt);
}
static int64_t GetLightInt(CQValue value) {
    return value.n >> 1;
}

static CQValue CreateLightFloat(float raw) {
    int32_t aa = *(int32_t *)&raw;
    int64_t bb = (int64_t)aa << 1;
    int64_t cc = bb & MaskLightFloat;
    return CQValueMake(cc);
}
static float GetLightFloat(CQValue value) {
    int64_t aa = value.n >> 1;
    int32_t bb = (int32_t)aa;
    float cc = *(float *)&bb;
    return cc;
}

//weight value

#define NAMESPACE_BEGIN namespace {
#define NAMESPACE_END   }

NAMESPACE_BEGIN

struct WeightValue {
    
    int32_t _retainCount;
    
    WeightValue() : _retainCount(1) {
    }
    void retain() {
        ++_retainCount;
    }
    void release() {
        if (--_retainCount <= 0) {
            delete this;
        }
    }
    
    virtual bool isInt64 () { return false; }
    virtual bool isDouble() { return false; }
    virtual bool isString() { return false; }
    virtual bool isTable () { return false; }
    
    virtual ~WeightValue() = default;
};

struct WeightInt64 : WeightValue {
    int64_t value = 0;
    bool isInt64() override {
        return true;
    }
};

struct WeightDouble : WeightValue {
    double value = 0;
    bool isDouble() override {
        return true;
    }
};

struct WeightString : WeightValue {
    string value;
    bool isString() {
        return true;
    }
};

struct WeightTable : WeightValue {
    
    vector<CQValue> table0;
    vector<CQValue> table1;
    
    virtual bool isTable() {
        return true;
    }
    
    void addItem(CQValue item0, CQValue item1) {
        CQRetain(item0);
        CQRetain(item1);
        table0.push_back(item0);
        table0.push_back(item1);
    }
    
    ~WeightTable() {
        for (CQValue value : table0) {
            CQRelease(value);
        }
        for (CQValue value : table1) {
            CQRelease(value);
        }
    }
};

NAMESPACE_END

//interfaces

CQValue CQCreateBool (bool    v) { return CreateLightBool (v); }
CQValue CQCreateInt8 (int8_t  v) { return CreateLightInt  (v); }
CQValue CQCreateInt16(int16_t v) { return CreateLightInt  (v); }
CQValue CQCreateInt32(int32_t v) { return CreateLightInt  (v); }
CQValue CQCreateFloat(float   v) { return CreateLightFloat(v); }

CQValue CQCreateInt64(int64_t value) {
    auto ptr = new WeightInt64;
    ptr->value = value;
    return CQValueMake(ptr);
}

CQValue CQCreateDouble(double value) {
    auto ptr = new WeightDouble;
    ptr->value = value;
    return CQValueMake(ptr);
}

template<class T> T CQGetNumber(CQValue value) {
    
    if (value.n == CQValueNull.n) {
        return 0;
    }
    if (IsLightBool(value)) {
        return (T)GetLightBool(value);
    }
    if (IsLightInt(value)) {
        return (T)GetLightInt(value);
    }
    if (IsLightFloat(value)) {
        return (T)GetLightFloat(value);
    }
    
    auto ptr = (WeightValue *)value.n;
    if (ptr->isInt64()) {
        return (T)((WeightInt64 *)ptr)->value;
    }
    if (ptr->isDouble()) {
        return (T)((WeightDouble *)ptr)->value;
    }
    
    return 0;
}

bool    CQGetBool  (CQValue v) { return CQGetNumber<bool   >(v); }
int8_t  CQGetInt8  (CQValue v) { return CQGetNumber<int8_t >(v); }
int16_t CQGetInt16 (CQValue v) { return CQGetNumber<int16_t>(v); }
int32_t CQGetInt32 (CQValue v) { return CQGetNumber<int32_t>(v); }
int64_t CQGetInt64 (CQValue v) { return CQGetNumber<int64_t>(v); }
float   CQGetFloat (CQValue v) { return CQGetNumber<float  >(v); }
double  CQGetDouble(CQValue v) { return CQGetNumber<double >(v); }

CQValue CQCreateString(const char *value, int32_t length) {
    auto ptr = new WeightString;
    if (value != nullptr && length > 0) {
        ptr->value.assign(value, length);
    }
    return CQValueMake(ptr);
}

static WeightString *CastWeightString(CQValue value) {
    if (!IsWeight(value)) {
        return nullptr;
    }
    if (!((WeightValue *)value.n)->isString()) {
        return nullptr;
    }
    return (WeightString *)value.n;
}

int32_t CQGetStringLength(CQValue value) {
    WeightString *ptr = CastWeightString(value);
    if (ptr != nullptr) {
        return (int32_t)ptr->value.length();
    } else {
        return 0;
    }
}

const char *CQGetStringValue(CQValue value) {
    WeightString *ptr = CastWeightString(value);
    if (ptr != nullptr) {
        return ptr->value.c_str();
    } else {
        return "";
    }
}

CQValue CQCreateTable(void) {
    auto ptr = new WeightTable;
    return CQValueMake(ptr);
}

static WeightTable *CastWeightTable(CQValue value) {
    if (!IsWeight(value)) {
        return nullptr;
    }
    if (!((WeightValue *)value.n)->isTable()) {
        return nullptr;
    }
    return (WeightTable *)value.n;
}

void CQAddTableItem(CQValue table, CQValue item0, CQValue item1) {
    WeightTable *ptr = CastWeightTable(table);
    if (ptr == nullptr) {
        return;
    }
    ptr->addItem(item0, item1);
}

int32_t CQGetTableSize(CQValue table) {
    WeightTable *ptr = CastWeightTable(table);
    if (ptr != nullptr) {
        return (int32_t)ptr->table0.size();
    } else {
        return 0;
    }
}

CQValue CQGetTableItem0(CQValue table, int32_t position) {
    WeightTable *ptr = CastWeightTable(table);
    if (ptr == nullptr) {
        return CQValueNull;
    }
    if (ptr->table0.size() <= position) {
        return CQValueNull;
    }
    
    return ptr->table0[position];
}

CQValue CQGetTableItem1(CQValue table, int32_t position) {
    WeightTable *ptr = CastWeightTable(table);
    if (ptr == nullptr) {
        return CQValueNull;
    }
    if (ptr->table1.size() <= position) {
        return CQValueNull;
    }
    
    return ptr->table1[position];
}

void CQRetain(CQValue value) {
    if (IsWeight(value)) {
        auto ptr = (WeightValue *)value.n;
        ptr->retain();
    }
}

void CQRelease(CQValue value) {
    if (IsWeight(value)) {
        auto ptr = (WeightValue *)value.n;
        ptr->release();
    }
}
