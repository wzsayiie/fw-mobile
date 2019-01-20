#include "filesystem.h"

bool is_path_sep(char ch) {
    if (ON_WINDOWS) {
        return ch == '/' || ch == '\\';
    } else /* ON_MAC */ {
        return ch == '/';
    }
}

static string read_path_item(const char **reader) {
    while (is_path_sep(**reader)) {
        ++(*reader);
    }
    if (**reader == '\0') {
        return "";
    }
    
    string item;
    while (!is_path_sep(**reader) && **reader != '\0') {
        item.append(1, **reader);
        ++(*reader);
    }
    return item;
}

vector<string> split_path(const string &path) {
    if (path.empty()) {
        return vector<string>();
    }
    
    vector<string> items;
    const char *reader = path.c_str();
    while (true) {
        string it = read_path_item(&reader);
        if (it.empty()) {
            break;
        }
        
        if (it == ".") {
            if (items.empty()) {
                items.push_back(".");
            }
        } else if (it == "..") {
            if (items.size() > 0 && items.back() != "..") {
                items.pop_back();
            } else {
                items.push_back("..");
            }
        } else {
            items.push_back(it);
        }
    }
    
    //if is root
    if (ON_OSX && is_path_sep(path[0])) {
        char sep[] = { PATH_SEP, '\0' };
        if (items.size() > 0) {
            items[0] = string(sep) + items[0];
        } else {
            items.push_back(sep);
        }
    }
    
    return items;
}

void append_path(string *out_path, const string &item) {
    if (out_path == nullptr || item.empty()) {
        return;
    }
    
    if (!out_path->empty() && !is_path_sep(out_path->back())) {
        out_path->append(1, PATH_SEP);
    }
    out_path->append(item);
}

string base_name(const string &path) {
    vector<string> items = split_path(path);
    if (items.size() > 0) {
        return items.back();
    } else {
        return "";
    }
}

string dir_path(const string &path) {
    vector<string> items = split_path(path);
    
    if (items.size() > 1) {
        
        string dir;
        for (auto it = items.begin(); it < items.end() - 1; ++it) {
            if (!dir.empty()) {
                dir.append(1, PATH_SEP);
            }
            dir.append(*it);
        }
        return dir;
        
    } else {
        
        return "";
    }
}

bool fread(const string &path, vector<char> *content) {
    if (path.empty() || content == nullptr) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return false;
    }
    
    const size_t buf_size = 1024;
    char buffer[buf_size];
    while (true) {
        size_t got_size = fread(buffer, 1, buf_size, file);
        content->insert(content->end(), buffer, buffer + got_size);
        if (got_size < buf_size) {
            break;
        }
    }
    
    fclose(file);
    return true;
}

bool fwrite(const string &path, const vector<char> &content) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }
    fwrite(content.data(), 1, content.size(), file);
    fclose(file);
    return true;
}
