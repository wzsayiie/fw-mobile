#pragma once

#include "cqvalue.hh"

_CQCTOOL_BEGIN_VERSION_NS

//NOTE:
//for string value in json, unicode code point("uXXXX") is not supported.
//so like this "xx \uxxxx xx" is illegal.
//cqJson expects utf-8 string.

struct cqJson {
    
    static cq::value parseString(const std::string &str, bool *error);
    static cq::value parseFile(const std::string &path, bool *fileErr, bool *parseErr);

    //if successful, return true.
    static bool writeFile(const std::string &path, const cq::value &value);

    static std::string terseJson(const cq::value &value);
    static std::string formattedJson(const cq::value &value);
};

_CQCTOOL_END_VERSION_NS
