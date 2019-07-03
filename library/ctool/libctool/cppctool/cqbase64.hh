#pragma once

#include "cqcppbasis.hh"

#include "CQCTOOL_NS.hh"
_CQCTOOL_BEGIN_NS

struct cqBase64 {
    
    static std::string fromBytes(const uint8_t *bytes, size_t size);
    static std::vector<uint8_t> decode(const std::string &base64);
};

_CQCTOOL_END_NS
