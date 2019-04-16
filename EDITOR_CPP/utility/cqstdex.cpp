#include "cqstdex.hh"

bool begins_with(const char *prefix, const char *str, const char *str_end) {
    if (prefix == nullptr || str >= str_end) {
        return false;
    }
    
    while (*prefix != '\0' && str != str_end) {
        if (*prefix++ != *str++) {
            return false;
        }
    }
    return *prefix == '\0';
}

bool ends_with(const char *suffix, const char *str, const char *str_end) {
    if (suffix == nullptr || str >= str_end) {
        return false;
    }
    
    size_t suffix_len = strlen(suffix);
    size_t str_len = str_end - str;
    if (suffix_len > str_len) {
        return false;
    }
    
    size_t offset = str_len - suffix_len;
    if (strncmp(suffix, str + offset, suffix_len) == 0) {
        return true;
    } else {
        return false;
    }
}

string::string() : std::string() {
}

string::string(const std::string &that) : std::string(that) {
}

//do not judge 'that' is null or not, keep consistent with std::string.
string::string(const char *that) : std::string(that) {
}

const string &string::operator=(const char *that) {
    assign(that);
    return *this;
}

string::operator const char *() const {
    return c_str();
}

bool string::has_prefix(const string &prefix) const {
    if (begins_with(prefix.c_str(), c_str(), c_str() + size())) {
        if (prefix.size() != size()) {
            return true;
        }
    }
    return false;
}

bool string::has_suffix(const string &suffix) const {
    if (ends_with(suffix.c_str(), c_str(), c_str() + size())) {
        if (suffix.size() != size()) {
            return true;
        }
    }
    return false;
}

const char *string::non_null(const char *value) {
    return value ? value : "";
}
