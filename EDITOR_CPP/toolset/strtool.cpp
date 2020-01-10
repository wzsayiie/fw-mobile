#include "strtool.hh"
#include <cstdarg>

//string prefix and suffix:

bool start_with(const string &prefix, const char *ptr, const char *end) {
    size_t size = prefix.size();
    if (size <= end - ptr) {
        return strncmp(prefix.c_str(), ptr, size) == 0;
    } else {
        return false;
    }
}

bool end_with(const string &suffix, const char *ptr, const char *end) {
    size_t size = suffix.size();
    if (size <= end - ptr) {
        return strncmp(suffix.c_str(), end - size, size) == 0;
    } else {
        return false;
    }
}

bool start_with(const string &prefix, const string &str) {
    return start_with(prefix, str.c_str(), str.c_str() + str.size());
}

bool end_with(const string &suffix, const string &str) {
    return end_with(suffix, str.c_str(), str.c_str() + str.size());
}

//format string:

static char _buffer[1024 * 1024];

#define format_args(BUFFER, SIZE, FORMAT)\
/**/do {\
/**/    va_list args;\
/**/    va_start(args, FORMAT);\
/**/    vsnprintf(BUFFER, SIZE, FORMAT, args);\
/**/    va_end(args);\
/**/} while (0)

void append_format(string *str, const char *format, ...) {
    if (str != nullptr) {
        format_args(_buffer, sizeof(_buffer), format);
        str->append(_buffer);
    }
}

void assign_format(string *str, const char *format, ...) {
    if (str != nullptr) {
        format_args(_buffer, sizeof(_buffer), format);
        str->assign(_buffer);
    }
}

//path string:

static string read_item(const char **ptr) {
    while (**ptr == *path_div) {
        *ptr += 1;
    }
    
    string item;
    while (**ptr != *path_div && **ptr != '\0') {
        item.append(1, **ptr);
        *ptr += 1;
    }
    return item;
}

vector<string> split_path(const string &path) {
    vector<string> items;
    const char *ptr = path.c_str();
    while (true) {
        string it = read_item(&ptr);
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
    if (!path.empty() && path[0] == *path_div) {
        if (!items.empty()) {
            items[0] = path_div + items[0];
        } else {
            items.push_back(path_div);
        }
    }
    
    return items;
}

string parent_dir_of(const string &path) {
    vector<string> items = split_path(path);
    string dir;
    for (auto it = items.begin(); it < items.end() - 1; ++it) {
        if (!dir.empty()) {
            dir.append(path_div);
        }
        dir.append(*it);
    }
    return dir;
}

string file_name_of(const string &path) {
    vector<string> items = split_path(path);
    if (!items.empty()) {
        return items.back();
    } else {
        return "";
    }
}

string join_path(const string &dir, const string &item) {
    if (dir.empty()) {
        return item;
    }
    
    if (item.empty()) {
        return dir;
    }
    
    string gen = dir;
    if (gen.back() != *path_div) {
        gen.append(path_div);
    }
    gen.append(item);
    
    return gen;
}

//code source extension:

bool is_src_file(const string &name) {
    static const vector<string> options = {
        ".h"   , ".hh" , ".hpp",
        ".cc"  , ".cxx", ".cpp",
        ".m"   , ".mm" ,
        ".cs"  ,
        ".java",
        ".lua" ,
    };
    for (auto &it : options) {
        if (end_with(it, name)) {
            return true;
        }
    }
    return false;
}
