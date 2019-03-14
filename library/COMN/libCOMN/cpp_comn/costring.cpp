#include "costring.hh"

void coString::setUTF8(int64_t data, int32_t length) {
    if (data != 0 && length > 0) {
        _value.append((const char *)data, length);
    } else {
        _value.clear();
    }
}

int64_t coString::utf8Data() {
    return (int64_t)_value.data();
}

int32_t coString::utf8Length() {
    return (int32_t)_value.length();
}
