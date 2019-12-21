#ifdef __APPLE__

#include "_fsys.hh"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

string getcwd() {
    char buf[512] = "\0";
    getcwd(buf, sizeof(buf));
    return buf;
}

bool chdir(const string &dir) {
    return chdir(dir.c_str()) == 0;
}

bool fexists(const string &path, bool *isdir) {
    struct stat info;
    int err = stat(path.c_str(), &info);
    
    if (!err) {
        if (isdir != nullptr) {
            *isdir = S_ISDIR(info.st_mode);
        }
        return true;
    } else {
        if (isdir != nullptr) {
            *isdir = false;
        }
        return false;
    }
}

vector<fitem> subitems(const string &dir, bool *err) {
    vector<fitem> subitem;
    
    auto state = opendir(dir.c_str());
    if (state == nullptr) {
        if (err != nullptr) {
            *err = true;
        }
        return subitem;
    }
    
    while (true) {
        dirent *ent = readdir(state);
        if (ent == nullptr) {
            break;
        }
        
        //ignore ".", ".." and hidden files.
        if (ent->d_name[0] == '.') {
            continue;
        }
        
        fitem it;
        it.isdir = (ent->d_type == DT_DIR);
        it.name = ent->d_name;
        subitem.push_back(it);
    }
    closedir(state);
    
    //NOTE: the list that readdir() returns is not sorted.
    auto cmp = [](const fitem &a, const fitem &b) {
        return a.name < b.name;
    };
    sort(subitem.begin(), subitem.end(), cmp);
    
    if (err != nullptr) {
        *err = false;
    }
    return subitem;
}

#endif
