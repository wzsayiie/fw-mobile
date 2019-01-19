#include "types.h"

bool has_prefix(const std::string &string, const std::string &prefix) {
    if (string.size() <= prefix.size()) {
        return false;
    }
    if (prefix.size() == 0) {
        return true;
    }
    
    if (strncmp(string.c_str(), prefix.c_str(), prefix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}

bool has_suffix(const std::string &string, const std::string &suffix) {
    if (string.size() <= suffix.size()) {
        return false;
    }
    if (suffix.size() == 0) {
        return true;
    }
    
    size_t offset = string.size() - suffix.size();
    if (strncmp(string.c_str() + offset, suffix.c_str(), suffix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}
