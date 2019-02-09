#include "cqahead.hh"

bool CQStringHasPrefix(const string &str, const string &prefix) {
    if (str.size() <= prefix.size()) {
        return false;
    }
    if (prefix.size() == 0) {
        return true;
    }
    
    if (strncmp(str.c_str(), prefix.c_str(), prefix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}

bool CQStringHasSuffix(const string &str, const string &suffix) {
    if (str.size() <= suffix.size()) {
        return false;
    }
    if (suffix.size() == 0) {
        return true;
    }
    
    size_t offset = str.size() - suffix.size();
    if (strncmp(str.c_str() + offset, suffix.c_str(), suffix.size()) == 0) {
        return true;
    } else {
        return false;
    }
}
