#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

struct cqBase64 {
    static std::string from(const void *bytes, size_t size);
    static std::vector<uint8_t> decode(const std::string &base64);
};

_CQCTOOL_END_VERSION_NS
