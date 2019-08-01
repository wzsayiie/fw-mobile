#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

struct cqPathString {
    
    static std::string append(const std::string &path, const std::string &item);
    
    static std::string localeDirectory(const std::string &path);
    static std::string fileName(const std::string &path);
    static std::string fileNameWithoutExtension(const std::string &path);
    static std::string extensionName(const std::string &path);
};

_CQCTOOL_END_VERSION_NS
