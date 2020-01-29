#include "strtool.hh"
#include <cstdarg>

char BYTE_BUF[BYTE_BUF_SIZE];

bool start_with(const string &word, const char *ptr, const char *end) {
    size_t size = word.size();
    if (size <= end - ptr) {
        return strncmp(word.c_str(), ptr, size) == 0;
    } else {
        return false;
    }
}

bool end_with(const string &word, const char *ptr, const char *end) {
    size_t size = word.size();
    if (size <= end - ptr) {
        return strncmp(word.c_str(), end - size, size) == 0;
    } else {
        return false;
    }
}

bool start_with(const string &word, const string &str) {
    return start_with(word, str.c_str(), str.c_str() + str.size());
}

bool end_with(const string &word, const string &str) {
    return end_with(word, str.c_str(), str.c_str() + str.size());
}

#define format_args(BUFFER, SIZE, FORMAT)\
/**/do {\
/**/    va_list args;\
/**/    va_start(args, FORMAT);\
/**/    vsnprintf(BUFFER, SIZE, FORMAT, args);\
/**/    va_end(args);\
/**/} while (0)

void append_format(string *str, const char *format, ...) {
    if (str != nullptr) {
        format_args(BYTE_BUF, BYTE_BUF_SIZE, format);
        str->append(BYTE_BUF);
    }
}

void assign_format(string *str, const char *format, ...) {
    if (str != nullptr) {
        format_args(BYTE_BUF, BYTE_BUF_SIZE, format);
        str->assign(BYTE_BUF);
    }
}

static string read_path_item(const char **ptr) {
    while (**ptr == *PATH_SEP) {
        *ptr += 1;
    }
    
    string item;
    while (**ptr != *PATH_SEP && **ptr != '\0') {
        item.append(1, **ptr);
        *ptr += 1;
    }
    return item;
}

vector<string> split_path(const string &path) {
    const char *ptr = path.c_str();
    
    vector<string> items;
    while (true) {
        string it = read_path_item(&ptr);
        if (it.empty()) {
            break;
        }
        
        if (it == ".") {
            if (items.empty()) {
                items.push_back(".");
            }
            
        } else if (it == "..") {
            if (items.size() > 0
             && items.back() != ".."
             && items.back() != ".")
            {
                items.pop_back();
            }
            else
            {
                items.push_back("..");
            }
            
        } else {
            items.push_back(it);
        }
    }
    
    //is the path start with root?
    IF_ON_POSIX({
        if (!path.empty() && path[0] == '/') {
            items.insert(items.begin(), "/");
        }
    });
    
    return items;
}

static const char *last_item_of(const string &path) {
    const char *head = path.c_str();
    const char *ptr  = path.c_str() + path.size() - 1;
    
    //skip the separators at end.
    while (ptr > head && *ptr == *PATH_SEP) {
        ptr -= 1;
    }
    
    //find the last separator.
    while (ptr > head && ptr[-1] != *PATH_SEP) {
        ptr -= 1;
    }
    
    return ptr;
}

string parent_dir_of(const string &path) {
    const char *item = last_item_of(path);
    
    //NOTE: keep the separator at parent's tail. parent of "/usr" is "/".
    return string(path.c_str(), item);
}

string file_name_of(const string &path) {
    const char *item = last_item_of(path);
    
    return string(item);
}

string join_path(const string &dir, const string &item) {
    if (dir.empty()) {
        return item;
    }
    
    if (item.empty()) {
        return dir;
    }
    
    string ret = dir;
    if (ret.back() != *PATH_SEP) {
        ret.append(PATH_SEP);
    }
    ret.append(item);
    
    return ret;
}

bool is_src_file(const string &name) {
    const char **ext = SRC_FILE_EXT;
    for (; *ext != nullptr; ++ext) {
        if (name.size() > strlen(*ext) && end_with(*ext, name)) {
            return true;
        }
    }
    
    return false;
}
