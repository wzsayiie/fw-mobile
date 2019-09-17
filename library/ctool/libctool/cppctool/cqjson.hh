#pragma once

#include "cqvalue.hh"

_CQCTOOL_BEGIN_VERSION_NS

//NOTE:
//for string value in json, unicode code point("uXXXX") is not supported.
//so like this "xx \uxxxx xx" is illegal.
//cqJson expects utf-8 string.

struct cqJson {
    
    //if succeeded, *position is INT_MAX, and the function return the value;
    //if failed, *position specifies the location of the error in the string, return null.
    static cq::value parseString(const std::string &string, int *position);
    
    //if succeeded, *position is INT_MAX, the funcntion return the value;
    //if read file failed, *position is -1, return null;
    //if parse json faild, *position specifies the location of the error in the file, return null.
    static cq::value parseFile(const std::string &path, int *position);

    //if successful, return true.
    static bool writeFile(const std::string &path, const cq::value &value);

    static std::string terseJson(const cq::value &value);
    static std::string formattedJson(const cq::value &value);
};

_CQCTOOL_END_VERSION_NS
