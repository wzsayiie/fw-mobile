#pragma once

#include "cqstdex.hh"

static const char *const CQUTF8BOM = "\xEF\xBB\xBF";
static const size_t CQUTF8BOMSize = 3;

bool CQStartsWithUTF8BOM(const char *ptr, const char *end);

inline bool CQStartsWithUTF8BOM(const vector<char> &bytes) {
    return CQStartsWithUTF8BOM(bytes.data(), bytes.data() + bytes.size());
}

size_t CQGetUTF8Char(const char *ptr, const char *end, char *ascii);

//if [ptr, end) is utf8 string, return true, else return false;
//*out is adjusted string, it doesn't start with BOM, and not include "\r" and "\r\n",
//*adjusted flags the adjustment happened or not.
bool CQUTF8Check(const char *ptr, const char *end, bool *adjusted, vector<char> *out);

inline bool CQUTF8Check(const vector<char> &bytes, bool *adjusted, vector<char> *out) {
    return CQUTF8Check(bytes.data(), bytes.data() + bytes.size(), adjusted, out);
}
