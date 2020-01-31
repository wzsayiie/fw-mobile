#include "fsystem.hh"
#include "strtool.hh"

//read and write file:

bool read_file(const string &path, vector<char> *out) {
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

bool write_file(const string &path, const vector<char> &dat) {
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

static void on_file(const string &name, int deep, traverse_fn fn) {
    traverse_item item; {
        item.file.is_dir = false;
        item.file.name = name;
        item.deep = deep;
    }
    fn(item);
}

static void for_dir(const string &name, int deep, traverse_fn fn) {
    //self:
    traverse_item item; {
        item.file.is_dir = true;
        item.file.name = name;
        item.deep = deep;
    }
    fn(item);
    
    //subitems:
    if (!goto_dir(name)) {
        return;
    }
    vector<file_info> sub_files = sub_files_of(".", nullptr);
    for (auto &it : sub_files) {
        if (it.is_dir) {
            for_dir(it.name, deep + 1, fn);
        } else {
            on_file(it.name, deep + 1, fn);
        }
    }
    goto_dir("..");
}

bool traverse(const string &path, traverse_fn fn) {
    if (path.empty() || fn == nullptr) {
        return false;
    }
    
    bool is_dir = false;
    if (!file_at(path, &is_dir)) {
        return false;
    }
    
    string origin = work_dir();
    {
        string parent = parent_dir_of(path);
        goto_dir(parent);
        
        string name = file_name_of(path);
        if (is_dir) {
            for_dir(name, 0, fn);
        } else {
            on_file(name, 0, fn);
        }
    }
    goto_dir(origin);
    
    return true;
}
