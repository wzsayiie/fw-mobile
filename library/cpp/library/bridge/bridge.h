#pragma once

#include "bridge_core.h"
#include <string>
#include <vector>
#include <map>

// stack parameters ->

template<typename T> struct BRGParam;

#define IMPL(TYPE, WRITER, READER) \
/**/    static void write(TYPE value) { \
/**/        WRITER(value); \
/**/    } \
/**/    static TYPE read() { \
/**/        return READER(); \
/**/    }

template<> struct BRGParam<bool   > { IMPL(bool   , BRGWriteBool  , BRGReadBool  ) };
template<> struct BRGParam<int8_t > { IMPL(int8_t , BRGWriteByte  , BRGReadByte  ) };
template<> struct BRGParam<short  > { IMPL(short  , BRGWriteShort , BRGReadShort ) };
template<> struct BRGParam<int    > { IMPL(int    , BRGWriteInt   , BRGReadInt   ) };
template<> struct BRGParam<int64_t> { IMPL(int64_t, BRGWriteLong  , BRGReadLong  ) };
template<> struct BRGParam<float  > { IMPL(float  , BRGWriteFloat , BRGReadFloat ) };
template<> struct BRGParam<double > { IMPL(double , BRGWriteDouble, BRGReadDouble) };

#undef IMPL

template<> struct BRGParam<std::string> {
    
    static void write(const std::string &string) {
        BRGWriteStringLength((int)string.size());
        BRGWriteStringValue(string.c_str(), (int)string.size());
    }
    
    static std::string read() {
        BRGReadStringLength();
        return BRGReadStringValue();
    }
};

template<typename T> struct BRGParam<std::vector<T>> {
    
    static void write(const std::vector<T> &vector) {
        BRGWriteArraySize((int)vector.size());
        for (auto item : vector) {
            BRGParam<T>::write(item);
        }
    }
    
    static std::vector<T> read() {
        int size = BRGReadArraySize();
        std::vector<T> vector( (size_t)size );
        for (int it = 0; it < size; ++it) {
            vector[it] = BRGParam<T>::read();
        }
        return vector;
    }
};

template<typename K, typename V> struct BRGParam<std::map<K, V>> {
    
    static void write(const std::map<K, V> &map) {
        BRGWriteMapSize((int)map.size());
        for (auto entry : map) {
            BRGParam<K>::write(entry->first);
            BRGParam<V>::write(entry->second);
        }
    }
    
    static std::map<K, V> read() {
        int size = BRGReadMapSize();
        std::map<K, V> map;
        for (int it = 0; it < size; ++it) {
            auto key   = BRGParam<K>::read();
            auto value = BRGParam<V>::read();
            map[key] = value;
        }
        return map;
    }
};

//object management ->

template<typename T> int BRGRetainCoreOfObject(int classID, T object) {
    return 0;
}

template<typename T> std::shared_ptr<T> BRGReleaseCoreFromID(int classID, int coreID) {
    return std::shared_ptr<T>();
}
