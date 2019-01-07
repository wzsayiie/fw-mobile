#pragma once

#include <stdint.h>

# ifdef ANDROID
#   include "bridge_core_android.h"
# endif

#ifdef __cplusplus
extern "C" <%
#endif

//stack parameters ->

typedef enum BRGType {

    //basic types:
    //
    //[A] 1 kinds of boolean types: bool;
    //[B] 4 kinds of integer types: byte(8 bit), short(16 bit), int(32 bit), long(64 bit);
    //[C] 2 kinds of float points : float, double.
    //
    BRGTypeBool   = 1,
    BRGTypeByte   = 2,
    BRGTypeShort  = 3,
    BRGTypeInt    = 4,
    BRGTypeLong   = 5,
    BRGTypeFloat  = 6,
    BRGTypeDouble = 7,
    
    //string type:
    //
    //BRGTypeStringLength marks the length of string's bytes;
    //BRGTypeStringValue marks the string value.
    //
    BRGTypeStringLength = 8,
    BRGTypeStringValue = 9,
    
    //array type:
    //
    //the flag marks start of array, and remembers count of items followed.
    //
    BRGTypeArraySize = 10,
    
    //map type:
    //
    //the flag marks start of a map, and remembers count of entries followed.
    //
    BRGTypeMapSize = 11,
}
BRGType;

//push a frame to current thread's stack.
void BRGPush(void);

//write a basic type's value to top stack frame.
void BRGWriteBool  (bool    value);
void BRGWriteByte  (int8_t  value);
void BRGWriteShort (short   value);
void BRGWriteInt   (int     value);
void BRGWriteLong  (int64_t value);
void BRGWriteFloat (float   value);
void BRGWriteDouble(double  value);

//write a string to top frame, 2 steps need:
//firstly write the length of string's bytes, secondly write the value of string.
//for example, write string "one" to top frame:
//
// |void Example_WriteString() {
// |  BRGWriteStringLength(3);
// |  BRGWriteStringValue("one", 3);
// |}
//
//note: only utf-8 string should be used.
//
void BRGWriteStringLength(int length);
void BRGWriteStringValue(const char *value, int length);

//write a array to top frame:
//
//firstly write count of items of array to the frame, after that write every item.
//for example, write array [10, 20, 30] to top frame:
//
// |void Example_WriteArray() {
// |  BRGWriteArraySize(3);
// |  BRGWriteInt(10);
// |  BRGWriteInt(20);
// |  BRGWriteInt(30);
// |}
//
void BRGWriteArraySize(int size);

//write a map to top frame:
//
//firstly write count of entries of map to eh frame, after that write every entry.
//for example, write dictionary { 10:"ten", 20: "twenty" } to top frame:
//
// |void Example_WriteMap() {
// |
// |  BRGWriteMapSize(2);
// |
// |  BRGWriteInt(10);
// |  BRGWriteStringLength(3);
// |  BRGWriteStringValue("ten", 3);
// |
// |  BRGWriteInt(20);
// |  BRGWriteStringLength(6);
// |  BRGWriteStringValue("twenty", 6);
// |}
//
void BRGWriteMapSize(int size);

//get type of item that will be read next from top frame.
BRGType BRGCheckType(void);

//read a basic type's item from top frame.
bool    BRGReadBool  (void);
int8_t  BRGReadByte  (void);
short   BRGReadShort (void);
int     BRGReadInt   (void);
int64_t BRGReadLong  (void);
float   BRGReadFloat (void);
double  BRGReadDouble(void);

//read a string from top frame:
//firstly read the length of string's bytes, after that read value of the string.
//for example:
//
// |void Example_ReadString() {
// |  int length = BRGReadStringLength();
// |  const char *string = BRGReadStringValue();
// |}
//
//note: the value returned by BRGReadStringValue() ends with a '\0', if it was not NULL.
//
int BRGReadStringLength(void);
const char *BRGReadStringValue(void);

//read a array from top frame:
//firstly read the count of items of array, after that read every item.
//for example, read a array that includes int values:
//
// |void Example_ReadArray() {
// |
// |  int size = BRGReadArraySize();
// |
// |  for (int it = 0; it < size; ++it) {
// |
// |    //itemType must be BRGTypeInt,
// |    //otherwise BRGReadInt() will get dirty data.
// |    BRGType itemType = BRGCheckType();
// |    int item = BRGReadInt();
// |  }
// |}
//
int BRGReadArraySize(void);

//read a map from top frame:
//firstly read count of entries of map, after that read every entry.
//for example, read a map which key is int type, which value is float type:
//
// |void Example_ReadMap() {
// |
// |  int size = BRGReadMapSize();
// |
// |  for (int it = 0; it < size; ++it) {
// |
// |    //keyType must be BRGTypeInt,
// |    //otherwise BRGReadInt() will get dirty data.
// |    BRGType keyType = BRGCheckType();
// |    int key = BRGReadInt();
// |
// |    //valueType must be BRGTypeFloat,
// |    //otherwise BRGReadFloat() will get dirty data.
// |    BRGType valueType = BRGCheckType();
// |    float value = BRGReadFloat();
// |  }
// |}
//
int BRGReadMapSize(void);

//pop frame of current thread's stack.
//parameter "count" specify count of frames popped.
void BRGPop(int count);

//object manager ->

typedef bool (*BRGTryRetainHandler )(int classID, int coreID);
typedef bool (*BRGTryReleaseHandler)(int classID, int coreID);
typedef bool (*BRGTryCallHandler   )(int classID, int methodID, int coreID);

void BRGAddTryRetainHandler (BRGTryRetainHandler  handler);
void BRGAddTryReleaseHandler(BRGTryReleaseHandler handler);
void BRGAddTryCallHandler   (BRGTryCallHandler    handler);

void BRGRetainCore (int classID, int coreID);
void BRGReleaseCore(int classID, int coreID);
void BRGCallMethod (int classID, int methodID, int coreID);

#ifdef __cplusplus
%>
#endif
