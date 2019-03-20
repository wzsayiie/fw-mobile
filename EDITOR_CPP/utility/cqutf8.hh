#pragma once

#include "cqstdex.hh"

static const char *const cqUTF8BOM = "\xEF\xBB\xBF";
static const size_t cqUTF8BOMSize = 3;

bool cqStartsWithUTF8BOM(const char *ptr, const char *end);

inline bool cqStartsWithUTF8BOM(const vector<char> &bytes) {
    return cqStartsWithUTF8BOM(bytes.data(), bytes.data() + bytes.size());
}

size_t cqGetUTF8Char(const char *ptr, const char *end, char *ascii);

//if [ptr, end) is utf8 string, return true, else return false;
//*out is adjusted string, it doesn't start with BOM, and not include "\r" and "\r\n",
//*adjusted flags the adjustment happened or not.
bool cqUTF8Check(const char *ptr, const char *end, bool *adjusted, vector<char> *out);

inline bool cqUTF8Check(const vector<char> &bytes, bool *adjusted, vector<char> *out) {
    return cqUTF8Check(bytes.data(), bytes.data() + bytes.size(), adjusted, out);
}
