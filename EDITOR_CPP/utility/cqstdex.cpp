#include "cqstdex.hh"

bool starts_with(const char *prefix, const char *str, const char *str_end) {
    if (prefix == nullptr || str > str_end) {
        return false;
    }
    
    while (*prefix != '\0' && str != str_end) {
        if (*prefix++ != *str++) {
            return false;
        }
    }
    return *prefix == '\0';
}

string::string() : std::string() {
}

string::string(const std::string &that) : std::string(that) {
}

string::string(const char *that) : std::string(non_null(that)) {
}

const string &string::operator=(const char *that) {
    assign(non_null(that));
    return *this;
}

string::operator const char *() const {
    return c_str();
}

bool string::has_prefix(const string &prefix) const {
    if (size() <= prefix.size()) {
        return false;
    }
    if (prefix.size() == 0) {
        return true;
    }
    
    if (strncmp(c_str(), prefix, prefix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}

bool string::has_suffix(const string &suffix) const {
    if (size() <= suffix.size()) {
        return false;
    }
    if (suffix.size() == 0) {
        return true;
    }
    
    size_t offset = size() - suffix.size();
    if (strncmp(c_str() + offset, suffix, suffix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}

const char *string::non_null(const char *value) {
    return value ? value : "";
}
