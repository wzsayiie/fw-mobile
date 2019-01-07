#include "bridge_core.h"
#include <vector>
#include <string>
#include <stack>

//stack parameters ->

struct BRGStackParam {
    
    BRGType type;
    
    union {
        bool    aBool  ;
        int8_t  aByte  ;
        short   aShort ;
        int     aInt   ;
        int64_t aLong  ;
        float   aFloat ;
        double  aDouble;
    };
    std::string aString;
    
    BRGStackParam(bool    value): type(BRGTypeBool  ), aBool  (value) {}
    BRGStackParam(int8_t  value): type(BRGTypeByte  ), aByte  (value) {}
    BRGStackParam(short   value): type(BRGTypeShort ), aShort (value) {}
    BRGStackParam(int     value): type(BRGTypeInt   ), aInt   (value) {}
    BRGStackParam(int64_t value): type(BRGTypeLong  ), aLong  (value) {}
    BRGStackParam(float   value): type(BRGTypeFloat ), aFloat (value) {}
    BRGStackParam(double  value): type(BRGTypeDouble), aDouble(value) {}
    
    //for BRGTypeStringLength, BRGTypeArraySize and BRGTypeMapSize
    BRGStackParam(BRGType type, int value): type(type), aInt(value) {}
    
    //for BRGTypeStringValue
    BRGStackParam(const char *value, int length) {
        this->type = BRGTypeStringValue;
        this->aString = std::string(value, (size_t)length);
        this->aLong = 0;
    }
};

struct BRGStackFrame {
    
    std::vector<BRGStackParam> params;
    int read = 0;
    
    BRGType checkType() { return params[read].type; }
    
    bool    readBool  () { return params[read++].aBool  ; }
    int8_t  readByte  () { return params[read++].aByte  ; }
    short   readShort () { return params[read++].aShort ; }
    int     readInt   () { return params[read++].aInt   ; }
    int64_t readLong  () { return params[read++].aLong  ; }
    float   readFloat () { return params[read++].aFloat ; }
    double  readDouble() { return params[read++].aDouble; }
    
    int readStringLength() { return params[read++].aInt; }
    const char *readStringValue() { return params[read++].aString.c_str(); }
    
    int readArraySize() { return params[read++].aInt; }
    int readMapSize  () { return params[read++].aInt; }
};

static std::stack<BRGStackFrame> *BRGStackGet() {
    
    //the function should return current thread's stack,
    //but that is not supported now.
    
    static std::stack<BRGStackFrame> *object = NULL;
    if (object == NULL) {
        object = new std::stack<BRGStackFrame>;
    }
    return object;
}

static BRGStackFrame *BRGStackTop() {
    return &(BRGStackGet()->top());
}

void BRGPush() {
    BRGStackGet()->push(BRGStackFrame());
}

void BRGWriteBool  (bool    value) { BRGStackTop()->params.push_back(value); }
void BRGWriteByte  (int8_t  value) { BRGStackTop()->params.push_back(value); }
void BRGWriteShort (short   value) { BRGStackTop()->params.push_back(value); }
void BRGWriteInt   (int     value) { BRGStackTop()->params.push_back(value); }
void BRGWriteLong  (int64_t value) { BRGStackTop()->params.push_back(value); }
void BRGWriteFloat (float   value) { BRGStackTop()->params.push_back(value); }
void BRGWriteDouble(double  value) { BRGStackTop()->params.push_back(value); }

void BRGWriteStringLength(int length) {
    BRGStackTop()->params.push_back(BRGStackParam(BRGTypeStringLength, length));
}
void BRGWriteStringValue(const char *value, int length) {
    BRGStackTop()->params.push_back(BRGStackParam(value, length));
}

void BRGWriteArraySize(int size) {
    BRGStackTop()->params.push_back(BRGStackParam(BRGTypeArraySize, size));
}

void BRGWriteMapSize(int size) {
    BRGStackTop()->params.push_back(BRGStackParam(BRGTypeMapSize, size));
}

BRGType BRGCheckType() {
    return BRGStackTop()->checkType();
}

bool    BRGReadBool  () { return BRGStackTop()->readBool  (); }
int8_t  BRGReadByte  () { return BRGStackTop()->readByte  (); }
short   BRGReadShort () { return BRGStackTop()->readShort (); }
int     BRGReadInt   () { return BRGStackTop()->readInt   (); }
int64_t BRGReadLong  () { return BRGStackTop()->readLong  (); }
float   BRGReadFloat () { return BRGStackTop()->readFloat (); }
double  BRGReadDouble() { return BRGStackTop()->readDouble(); }

int BRGReadStringLength() {
    return BRGStackTop()->readStringLength();
}
const char *BRGReadStringValue() {
    return BRGStackTop()->readStringValue();
}

int BRGReadArraySize() {
    return BRGStackTop()->readArraySize();
}

int BRGReadMapSize() {
    return BRGStackTop()->readMapSize();
}

void BRGPop(int count) {
    while (count-- > 0) {
        BRGStackGet()->pop();
    }
}

//object manager ->

template<typename T> struct BRGHandlers {

    static std::vector<T> *sHandlers;

    static void add(T handler) {
        if (handler == NULL) {
            return;
        }
        if (sHandlers == NULL) {
            sHandlers = new std::vector<T>;
        }
    }

    template<typename... A> static void call(A... args) {
        if (sHandlers == NULL) {
            return;
        }
        for (auto it : *sHandlers) {
            bool handled = it(args...);
            if (handled) {
                return;
            }
        }
    }
};
template<typename T> std::vector<T> *BRGHandlers<T>::sHandlers = NULL;

void BRGAddTryRetainHandler (BRGTryRetainHandler  h) { BRGHandlers<BRGTryRetainHandler >::add(h); }
void BRGAddTryReleaseHandler(BRGTryReleaseHandler h) { BRGHandlers<BRGTryReleaseHandler>::add(h); }
void BRGAddTryCallHandler   (BRGTryCallHandler    h) { BRGHandlers<BRGTryCallHandler   >::add(h); }

void BRGRetainCore (int cls, int co    ) { BRGHandlers<BRGTryRetainHandler >::call(cls, co); }
void BRGReleaseCore(int cls, int co    ) { BRGHandlers<BRGTryReleaseHandler>::call(cls, co); }
void BRGCallMethod (int z, int m, int c) { BRGHandlers<BRGTryCallHandler   >::call(z, m, c); }
