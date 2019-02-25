#include "cqbridgecore_p.h"
#include <string>
#include <vector>

using namespace std;

const CQType CQTypeNull   =  3;
const CQType CQTypeBool   =  5;
const CQType CQTypeInt8   =  7;
const CQType CQTypeInt16  = 11;
const CQType CQTypeInt32  = 13;
const CQType CQTypeInt64  = 17;
const CQType CQTypeFloat  = 19;
const CQType CQTypeDouble = 23;
const CQType CQTypeString = 31;
const CQType CQTypeTable  = 37;

//light value

struct CQLightValue {
    int32_t type;
    union {
        bool    aBool;
        int8_t  aInt8;
        int16_t aInt16;
        int32_t aInt32;
        float   aFloat;
    };
};

static CQLightValue *CQLightCast(CQValue value) {
    auto casted = (CQLightValue *)&value;
    
    switch (casted->type) {
        case CQTypeBool : return casted;
        case CQTypeInt8 : return casted;
        case CQTypeInt16: return casted;
        case CQTypeInt32: return casted;
        case CQTypeFloat: return casted;

        default: return nullptr;
    }
}

//weight value

struct CQWeightValue {
    
    virtual ~CQWeightValue() = default;
    virtual CQType type() = 0;
    
    CQWeightValue();
    void retain();
    void release();
    
private:
    
    int32_t _retainCount;
};

CQWeightValue::CQWeightValue() {
    _retainCount = 1;
}
void CQWeightValue::retain() {
    _retainCount += 1;
}
void CQWeightValue::release() {
    if (_retainCount-- <= 1) {
        delete this;
    }
}

static CQWeightValue *CQWeightCast(CQValue value) {
    if (value.handle == 0) {
        return nullptr;
    }
    if (CQLightCast(value) != nullptr) {
        return nullptr;
    }
    
    return (CQWeightValue *)value.handle;
}

//weight int64

struct CQInt64 : CQWeightValue {
    
    CQInt64(int64_t value);
    CQType type() override;
    
    int64_t value;
};

CQInt64::CQInt64(int64_t value) : value(value) {
}
CQType CQInt64::type() {
    return CQTypeInt64;
}

//weight double

struct CQDouble : CQWeightValue {
    
    CQDouble(double value);
    CQType type() override;
    
    double value;
};

CQDouble::CQDouble(double value) : value(value) {
}
CQType CQDouble::type() {
    return CQTypeDouble;
}

//weight string

struct CQString : CQWeightValue {
    
    CQString(const char *raw, int32_t len);
    CQType type() override;
    
    string value;
};

CQString::CQString(const char *raw, int32_t len) : value(raw, len) {
}
CQType CQString::type() {
    return CQTypeString;
}

static CQString *CQStringCast(CQValue value) {
    if (auto it = CQWeightCast(value)) {
        if (it->type() == CQTypeString) {
            return (CQString *)it;
        }
    }
    return nullptr;
}

//weight table

struct CQTable :CQWeightValue {
    
    CQType type() override;
    void addItem(CQValue item0, CQValue item1);
    ~CQTable();
    
    vector<CQValue> table[2];
};

CQType CQTable::type() {
    return CQTypeTable;
}
void CQTable::addItem(CQValue item0, CQValue item1) {
    CQRetain(item0);
    CQRetain(item1);
    table[0].push_back(item0);
    table[1].push_back(item1);
}
CQTable::~CQTable() {
    for (auto it : table[0]) {
        CQRelease(it);
    }
    for (auto it : table[1]) {
        CQRelease(it);
    }
}

static CQTable *CQTableCast(CQValue value) {
    if (auto it = CQWeightCast(value)) {
        if (it->type() == CQTypeTable) {
            return (CQTable *)it;
        }
    }
    return nullptr;
}

//interfaces

CQType CQCheckType(CQValue value) {
    if (auto it = CQLightCast(value)) {
        return it->type;
    }
    if (auto it = CQWeightCast(value)) {
        return it->type();
    }
    return CQTypeNull;
}

template<class T> CQValue CQCreateLight(CQType type, T raw) {
    CQLightValue value = {type, 0};
    
    char *ptr = (char *)&value + 4;
    *(T *)ptr = raw;
    
    return *(CQValue *)&value;
}

CQValue CQCreateBool (bool    r) { return CQCreateLight(CQTypeBool , r); }
CQValue CQCreateInt8 (int8_t  r) { return CQCreateLight(CQTypeInt8 , r); }
CQValue CQCreateInt16(int16_t r) { return CQCreateLight(CQTypeInt16, r); }
CQValue CQCreateInt32(int32_t r) { return CQCreateLight(CQTypeInt32, r); }
CQValue CQCreateFloat(float   r) { return CQCreateLight(CQTypeFloat, r); }

CQValue CQCreateInt64 (int64_t r) { return CQValueMake(new CQInt64 (r)); }
CQValue CQCreateDouble(double  r) { return CQValueMake(new CQDouble(r)); }

template<class T> T CQGetNumber(CQValue value) {
    if (auto it = CQLightCast(value)) {
        switch (it->type) {
            case CQTypeBool : return (T)it->aBool ;
            case CQTypeInt8 : return (T)it->aInt8 ;
            case CQTypeInt16: return (T)it->aInt16;
            case CQTypeInt32: return (T)it->aInt32;
            case CQTypeFloat: return (T)it->aFloat;
            default:;
        }
    }
    
    if (auto it = CQWeightCast(value)) {
        switch (it->type()) {
            case CQTypeInt64 : return (T)((CQInt64  *)it)->value;
            case CQTypeDouble: return (T)((CQDouble *)it)->value;
            default:;
        }
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

CQValue CQCreateString(const char *raw, int32_t len) {
    return CQValueMake(new CQString(raw, len));
}

int32_t CQGetStringLength(CQValue value) {
    if (auto it = CQStringCast(value)) {
        return (int32_t)it->value.length();
    }
    return 0;
}

const char *CQGetStringValue(CQValue value) {
    if (auto it = CQStringCast(value)) {
        return it->value.c_str();
    }
    return "";
}

CQValue CQCreateTable(void) {
    return CQValueMake(new CQTable);
}

void CQAddTableItem(CQValue table, CQValue item0, CQValue item1) {
    if (auto it = CQTableCast(table)) {
        it->addItem(item0, item1);
    }
}

int32_t CQGetTableSize(CQValue table) {
    if (auto it = CQTableCast(table)) {
        return (int32_t)it->table[0].size();
    }
    return 0;
}

static CQValue CQGetTableItem(CQValue table, int32_t index, int32_t position) {
    if (auto it = CQTableCast(table)) {
        vector<CQValue> &tab = it->table[index];
        if (0 <= position && position < tab.size()) {
            return tab[position];
        }
    }
    return CQValueNull;
}

CQValue CQGetTableItem0(CQValue t, int32_t p) { return CQGetTableItem(t, 0, p); }
CQValue CQGetTableItem1(CQValue t, int32_t p) { return CQGetTableItem(t, 1, p); }

void CQRetain(CQValue value) {
    if (auto it = CQWeightCast(value)) {
        it->retain();
    }
}

void CQRelease(CQValue value) {
    if (auto it = CQWeightCast(value)) {
        it->release();
    }
}
