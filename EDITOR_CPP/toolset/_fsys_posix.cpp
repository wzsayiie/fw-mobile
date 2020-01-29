#ifdef __APPLE__

#include "_fsys.hh"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

string cur_dir() {
    char buf[512] = "\0";
    getcwd(buf, sizeof(buf));
    return buf;
}

bool goto_dir(const string &dir) {
    return chdir(dir.c_str()) == 0;
}

bool file_at(const string &path, bool *is_dir) {
    struct stat info;
    int err = stat(path.c_str(), &info);
    
    if (!err) {
        if (is_dir != nullptr) {
            *is_dir = S_ISDIR(info.st_mode);
        }
        return true;
    } else {
        if (is_dir != nullptr) {
            *is_dir = false;
        }
        return false;
    }
}

vector<file_info> sub_files_of(const string &dir, bool *err) {
    vector<file_info> info_list;
    
    auto state = opendir(dir.c_str());
    if (state == nullptr) {
        if (err != nullptr) {
            *err = true;
        }
        return info_list;
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
        
        file_info info;
        info.is_dir = (ent->d_type == DT_DIR);
        info.name = ent->d_name;
        info_list.push_back(info);
    }
    closedir(state);
    
    //NOTE: the list that readdir() returns is not sorted.
    auto cmp = [](const file_info &a, const file_info &b) {
        return a.name < b.name;
    };
    sort(info_list.begin(), info_list.end(), cmp);
    
    if (err != nullptr) {
        *err = false;
    }
    return info_list;
}

#endif
