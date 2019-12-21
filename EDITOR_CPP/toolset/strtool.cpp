#include "strtool.hh"

//string prefix and suffix:

bool startwith(const string &prefix, const char *ptr, const char *end) {
    size_t size = prefix.size();
    if (size <= end - ptr) {
        return strncmp(prefix.c_str(), ptr, size) == 0;
    } else {
        return false;
    }
}

bool endwith(const string &suffix, const char *ptr, const char *end) {
    size_t size = suffix.size();
    if (size <= end - ptr) {
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

//path string:

static string readpitem(const char **ptr) {
    while (**ptr == *pathdiv) {
        *ptr += 1;
    }
    
    string item;
    while (**ptr != *pathdiv && **ptr != '\0') {
        item.append(1, **ptr);
        *ptr += 1;
    }
    return item;
}

vector<string> splitpath(const string &path) {
    vector<string> items;
    const char *ptr = path.c_str();
    while (true) {
        string it = readpitem(&ptr);
        if (it.empty()) {
            break;
        }
        
        if (it == ".") {
            if (items.empty()) {
                items.push_back(".");
            }
        } else if (it == "..") {
            if (!items.empty() && items.back() != "." && items.back() != "..") {
                items.pop_back();
            } else {
                items.push_back("..");
            }
        } else {
            items.push_back(it);
        }
    }
    
    //is root path?
    if (!path.empty() && path[0] == *pathdiv) {
        if (!items.empty()) {
            items[0] = pathdiv + items[0];
        } else {
            items.push_back(pathdiv);
        }
    }
    
    return items;
}

string basename(const string &path) {
    vector<string> items = splitpath(path);
    if (!items.empty()) {
        return items.back();
    } else {
        return "";
    }
}

string dirname(const string &path) {
    vector<string> items = splitpath(path);
    string dir;
    for (auto it = items.begin(); it < items.end() - 1; ++it) {
        if (!dir.empty()) {
            dir.append(pathdiv);
        }
        dir.append(*it);
    }
    return dir;
}

string joinpath(const string &dir, const string &subitem) {
    if (dir.empty()) {
        return subitem;
    }
    
    if (subitem.empty()) {
        return dir;
    }
    
    string gen = dir;
    if (gen.back() != *pathdiv) {
        gen.append(pathdiv);
    }
    gen.append(subitem);
    
    return gen;
}

//code source extension:

bool codext(const string &name) {
    static const vector<string> options = {
        ".h" , ".hh" , ".cpp", ".cxx", ".cc",
        ".m" , ".mm" ,
        ".cs",".java", ".lua"
    };
    for (auto &it : options) {
        if (endwith(it, name)) {
            return true;
        }
    }
    return false;
}
