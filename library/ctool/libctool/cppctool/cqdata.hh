#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

struct cqData {
    static bool readFromFile(const std::string &path, std::vector<uint8_t> *data);
    static bool writeToFile(const std::string &path, const std::vector<uint8_t> &data);
};

_CQCTOOL_END_VERSION_NS
