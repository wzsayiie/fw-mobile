#include "strtool.hh"

//string prefix and suffix:

bool startwith(const string &prefix, const char *ptr, const char *end) {
    size_t size = prefix.size();
    if (size >= end - ptr) {
        return strncmp(prefix.c_str(), ptr, size) == 0;
    } else {
        return false;
    }
}

bool endwith(const string &suffix, const char *ptr, const char *end) {
    size_t size = suffix.size();
    if (size >= end - ptr) {
        return strncmp(suffix.c_str(), end - size, size) == 0;
    } else {
        return false;
    }
}

bool startwith(const string &prefix, const string &str) {
    return startwith(prefix, str.c_str(), str.c_str() + str.size());
}

bool endwith(const string &suffix, const string &str) {
    return endwith(suffix, str.c_str(), str.c_str() + str.size());
}
