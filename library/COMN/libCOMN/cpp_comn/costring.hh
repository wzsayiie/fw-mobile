#pragma once

#include "istring.hh"

struct coString : iString {

    void setUTF8(int64_t data, int32_t length) override;
    int64_t utf8Data() override;
    int32_t utf8Length() override;
    
private:
    
    std::string _value;
};
