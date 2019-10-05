#include "fsystem.hh"

//path string operation:

static string readpitem(const char **ptr) {
    while (**ptr == pathdiv) {
        *ptr += 1;
    }
    
    string item;
    while (**ptr != pathdiv && **ptr != '\0') {
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
    if (!path.empty() && path[0] == pathdiv) {
        char div[] = { pathdiv, '\0' };
        if (!items.empty()) {
            items[0] = div + items[0];
        } else {
            items.push_back(div);
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
            dir.append(1, pathdiv);
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
    if (gen.back() != pathdiv) {
        gen.append(1, pathdiv);
    }
    gen.append(subitem);
    
    return gen;
}

//read and write file:

bool readf(const string &path, vector<char> *out) {
    if (path.empty() || out == nullptr) {
        return false;
    }
    
    out->clear();
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return false;
    }
    while (!feof(file)) {
        char buf[1024];
        size_t len = fread(buf, 1, sizeof(buf), file);
        out->insert(out->end(), buf, buf + len);
    }
    fclose(file);
    
    return true;
}

bool writef(const string &path, const vector<char> &content) {
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

//traverse directory:

static void onfile(const string &name, int deep, scanfn fn) {
    fitem item;
    item.name = name;
    item.isdir = false;
    fn(item, deep);
}

static void ondir(const string &name, int deep, scanfn fn) {
    //self:
    fitem item;
    item.name = name;
    item.isdir = true;
    fn(item, deep);
    
    //subitems:
    if (!chdir(name)) {
        return;
    }
    vector<fitem> items = subitems(".", nullptr);
    for (auto &it : items) {
        if (it.isdir) {
            ondir(it.name, deep + 1, fn);
        } else {
            onfile(it.name, deep + 1, fn);
        }
    }
    chdir("..");
}

void scan(const string &path, scanfn fn) {
    if (path.empty() || fn == nullptr) {
        return;
    }
    
    bool isdir = false;
    if (!fexists(path, &isdir)) {
        return;
    }
    
    string origin = getcwd();
    {
        string parent = dirname(path);
        string name = basename(path);
        chdir(parent);
        
        if (isdir) {
            ondir(name, 0, fn);
        } else {
            onfile(name, 0, fn);
        }
    }
    chdir(origin);
}
