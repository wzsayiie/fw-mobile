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
        
        if (it == "..") {
            if (items.size() > 0) {
                items.pop_back();
            }
        } else if (it != ".") {
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
    if (out_path == NULL || item.empty()) {
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
