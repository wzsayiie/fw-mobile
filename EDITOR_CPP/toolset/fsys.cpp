#include "fsys.hh"
#include "strtool.hh"

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

bool writef(const string &path, const vector<char> &dat) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }
    fwrite(dat.data(), 1, dat.size(), file);
    fclose(file);
    
    return true;
}

//traverse directory:

static void onfile(const string &name, int deep, scanfn fn) {
    fitem item;
    item.isdir = false;
    item.name = name;
    fn(item, deep);
}

static void ondir(const string &name, int deep, scanfn fn) {
    //self:
    fitem item;
    item.isdir = true;
    item.name = name;
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

bool scan(const string &path, scanfn fn) {
    if (path.empty() || fn == nullptr) {
        return false;
    }
    
    bool isdir = false;
    if (!fexists(path, &isdir)) {
        return false;
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
    
    return true;
}
