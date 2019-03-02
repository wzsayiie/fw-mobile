#include "cqbridgecore.h"
#include <string>
#include <vector>

using namespace std;

const CQBridgeType CQBridgeTypeNull   =  3;
const CQBridgeType CQBridgeTypeBool   =  5;
const CQBridgeType CQBridgeTypeInt8   =  7;
const CQBridgeType CQBridgeTypeInt16  = 11;
const CQBridgeType CQBridgeTypeInt32  = 13;
const CQBridgeType CQBridgeTypeInt64  = 17;
const CQBridgeType CQBridgeTypeFloat  = 19;
const CQBridgeType CQBridgeTypeDouble = 23;
const CQBridgeType CQBridgeTypeString = 31;
const CQBridgeType CQBridgeTypeTable  = 37;

//light value

struct CQBridgeLightValue {
    int32_t type;
    union {
        bool    aBool;
        int8_t  aInt8;
        int16_t aInt16;
        int32_t aInt32;
        float   aFloat;
    };
};

static CQBridgeLightValue *CQBridgeLightCast(CQBridgeValue value) {
    auto casted = (CQBridgeLightValue *)&value;
    
    switch (casted->type) {
        case CQBridgeTypeBool : return casted;
        case CQBridgeTypeInt8 : return casted;
        case CQBridgeTypeInt16: return casted;
        case CQBridgeTypeInt32: return casted;
        case CQBridgeTypeFloat: return casted;

        default: return nullptr;
    }
}

//weight value

struct CQBridgeWeightValue {
    
    virtual ~CQBridgeWeightValue() = default;
    virtual CQBridgeType type() = 0;
    
    CQBridgeWeightValue();
    void retain();
    void release();
    
private:
    
    int32_t _retainCount;
};

CQBridgeWeightValue::CQBridgeWeightValue() {
    _retainCount = 1;
}
void CQBridgeWeightValue::retain() {
    _retainCount += 1;
}
void CQBridgeWeightValue::release() {
    if (_retainCount-- <= 1) {
        delete this;
    }
}

static CQBridgeWeightValue *CQBridgeWeightCast(CQBridgeValue value) {
    if (value.handle == 0) {
        return nullptr;
    }
    if (CQBridgeLightCast(value) != nullptr) {
        return nullptr;
    }
    
    return (CQBridgeWeightValue *)value.handle;
}

//weight int64

struct CQBridgeInt64 : CQBridgeWeightValue {
    
    CQBridgeInt64(int64_t value);
    CQBridgeType type() override;
    
    int64_t value;
};

CQBridgeInt64::CQBridgeInt64(int64_t value) : value(value) {
}
CQBridgeType CQBridgeInt64::type() {
    return CQBridgeTypeInt64;
}

//weight double

struct CQBridgeDouble : CQBridgeWeightValue {
    
    CQBridgeDouble(double value);
    CQBridgeType type() override;
    
    double value;
};

CQBridgeDouble::CQBridgeDouble(double value) : value(value) {
}
CQBridgeType CQBridgeDouble::type() {
    return CQBridgeTypeDouble;
}

//weight string

struct CQBridgeString : CQBridgeWeightValue {
    
    CQBridgeString(const char *raw, int32_t len);
    CQBridgeType type() override;
    
    string value;
};

CQBridgeString::CQBridgeString(const char *raw, int32_t len) : value(raw, len) {
}
CQBridgeType CQBridgeString::type() {
    return CQBridgeTypeString;
}

static CQBridgeString *CQBridgeStringCast(CQBridgeValue value) {
    if (auto it = CQBridgeWeightCast(value)) {
        if (it->type() == CQBridgeTypeString) {
            return (CQBridgeString *)it;
        }
    }
    return nullptr;
}

//weight table

struct CQBridgeTable :CQBridgeWeightValue {
    
    CQBridgeType type() override;
    void add(CQBridgeValue key, CQBridgeValue value);
    ~CQBridgeTable();
    
    vector<CQBridgeValue> table[2];
};

CQBridgeType CQBridgeTable::type() {
    return CQBridgeTypeTable;
}
void CQBridgeTable::add(CQBridgeValue key, CQBridgeValue value) {
    CQBridgeRetain(key);
    CQBridgeRetain(value);
    table[0].push_back(key);
    table[1].push_back(value);
}
CQBridgeTable::~CQBridgeTable() {
    for (auto it : table[0]) {
        CQBridgeRelease(it);
    }
    for (auto it : table[1]) {
        CQBridgeRelease(it);
    }
}

static CQBridgeTable *CQBridgeTableCast(CQBridgeValue value) {
    if (auto it = CQBridgeWeightCast(value)) {
        if (it->type() == CQBridgeTypeTable) {
            return (CQBridgeTable *)it;
        }
    }
    return nullptr;
}

//interfaces

CQBridgeType CQBridgeCheckType(CQBridgeValue value) {
    if (auto it = CQBridgeLightCast(value)) {
        return it->type;
    }
    if (auto it = CQBridgeWeightCast(value)) {
        return it->type();
    }
    return CQBridgeTypeNull;
}

template<class T> CQBridgeValue CQBridgeCreateLight(CQBridgeType type, T raw) {
    CQBridgeLightValue value = {type, 0};
    
    char *ptr = (char *)&value + 4;
    *(T *)ptr = raw;
    
    return *(CQBridgeValue *)&value;
}

CQBridgeValue CQBridgeCreateBool (bool    r) { return CQBridgeCreateLight(CQBridgeTypeBool , r); }
CQBridgeValue CQBridgeCreateInt8 (int8_t  r) { return CQBridgeCreateLight(CQBridgeTypeInt8 , r); }
CQBridgeValue CQBridgeCreateInt16(int16_t r) { return CQBridgeCreateLight(CQBridgeTypeInt16, r); }
CQBridgeValue CQBridgeCreateInt32(int32_t r) { return CQBridgeCreateLight(CQBridgeTypeInt32, r); }
CQBridgeValue CQBridgeCreateFloat(float   r) { return CQBridgeCreateLight(CQBridgeTypeFloat, r); }

CQBridgeValue CQBridgeCreateInt64 (int64_t r) { return CQBridgeValueMake(new CQBridgeInt64 (r)); }
CQBridgeValue CQBridgeCreateDouble(double  r) { return CQBridgeValueMake(new CQBridgeDouble(r)); }

template<class T> T CQBridgeGetNumber(CQBridgeValue value) {
    if (auto it = CQBridgeLightCast(value)) {
        switch (it->type) {
            case CQBridgeTypeBool : return (T)it->aBool ;
            case CQBridgeTypeInt8 : return (T)it->aInt8 ;
            case CQBridgeTypeInt16: return (T)it->aInt16;
            case CQBridgeTypeInt32: return (T)it->aInt32;
            case CQBridgeTypeFloat: return (T)it->aFloat;
            default:;
        }
    }
    
    if (auto it = CQBridgeWeightCast(value)) {
        switch (it->type()) {
            case CQBridgeTypeInt64 : return (T)((CQBridgeInt64  *)it)->value;
            case CQBridgeTypeDouble: return (T)((CQBridgeDouble *)it)->value;
            default:;
        }
    }
    
    return 0;
}

bool    CQBridgeGetBool  (CQBridgeValue v) { return CQBridgeGetNumber<bool   >(v); }
int8_t  CQBridgeGetInt8  (CQBridgeValue v) { return CQBridgeGetNumber<int8_t >(v); }
int16_t CQBridgeGetInt16 (CQBridgeValue v) { return CQBridgeGetNumber<int16_t>(v); }
int32_t CQBridgeGetInt32 (CQBridgeValue v) { return CQBridgeGetNumber<int32_t>(v); }
int64_t CQBridgeGetInt64 (CQBridgeValue v) { return CQBridgeGetNumber<int64_t>(v); }
float   CQBridgeGetFloat (CQBridgeValue v) { return CQBridgeGetNumber<float  >(v); }
double  CQBridgeGetDouble(CQBridgeValue v) { return CQBridgeGetNumber<double >(v); }

CQBridgeValue CQBridgeCreateString(const char *raw, int32_t len) {
    return CQBridgeValueMake(new CQBridgeString(raw, len));
}

int32_t CQBridgeStringLength(CQBridgeValue value) {
    if (auto it = CQBridgeStringCast(value)) {
        return (int32_t)it->value.length();
    }
    return 0;
}

const char *CQBridgeStringValue(CQBridgeValue value) {
    if (auto it = CQBridgeStringCast(value)) {
        return it->value.c_str();
    }
    return "";
}

CQBridgeValue CQBridgeCreateTable(void) {
    return CQBridgeValueMake(new CQBridgeTable);
}

void CQBridgeTableAdd(CQBridgeValue table, CQBridgeValue key, CQBridgeValue value) {
    if (auto it = CQBridgeTableCast(table)) {
        it->add(key, value);
    }
}

int32_t CQBridgeTableSize(CQBridgeValue table) {
    if (auto it = CQBridgeTableCast(table)) {
        return (int32_t)it->table[0].size();
    }
    return 0;
}

static CQBridgeValue CQBridgeTableGet(CQBridgeValue table, int32_t index, int32_t position) {
    if (auto it = CQBridgeTableCast(table)) {
        vector<CQBridgeValue> &tab = it->table[index];
        if (0 <= position && position < tab.size()) {
            return tab[position];
        }
    }
    return CQBridgeValueNull;
}

CQBridgeValue CQBridgeTableGetKey  (CQBridgeValue t, int32_t p) { return CQBridgeTableGet(t, 0, p); }
CQBridgeValue CQBridgeTableGetValue(CQBridgeValue t, int32_t p) { return CQBridgeTableGet(t, 1, p); }

void CQBridgeRetain(CQBridgeValue value) {
    if (auto it = CQBridgeWeightCast(value)) {
        it->retain();
    }
}

void CQBridgeRelease(CQBridgeValue value) {
    if (auto it = CQBridgeWeightCast(value)) {
        it->release();
    }
}
