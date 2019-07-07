#pragma once

#include "cqcppbasis.hh"

#include "CQCTOOL_NS.hh"
_CQCTOOL_BEGIN_NS

cq_class(cqData, cqObject) {
    
    static cqDataRef createWithData(cqDataRef that);
    static cqDataRef createWithBytes(const void *bytes, size_t size);
    static cqDataRef createWithContentsOfFile(const std::string &path);
    static cqDataRef createWithBase64EncodedData(const std::string &encoded);
    
    virtual const std::vector<uint8_t> &data();
    virtual const void *bytes();
    virtual size_t size();
    
    virtual bool writeToFile(const std::string &path);
    
    virtual std::string base64EncodedString();
};

_CQCTOOL_END_NS
