#include "_fsys.hh"
#include "macro.hh"

#if ON_WIN32()

#include <windows.h>

string work_dir() {
    CHAR szBuffer[512] = "\0";
    GetCurrentDirectoryA(sizeof(szBuffer), szBuffer);
    return szBuffer;
}

bool goto_dir(const string &dir) {
    return SetCurrentDirectoryA(dir.c_str());
}

bool file_at(const string &path, bool *is_dir) {
    DWORD dwAttributes = GetFileAttributesA(path.c_str());
    if (dwAttributes != INVALID_FILE_ATTRIBUTES) {
        if (is_dir != nullptr) {
            *is_dir = (dwAttributes & FILE_ATTRIBUTE_DIRECTORY);
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
    if (dir.empty()) {
        if (err != nullptr) {
            *err = true;
        }
        return vector<file_info>();
    }

    string target = join_path(dir, "*");
    vector<file_info> info_list;

    WIN32_FIND_DATAA stData;
    HANDLE hState = FindFirstFileA(target.c_str(), &stData);
    if (hState == INVALID_HANDLE_VALUE) {
        if (err != nullptr) {
            *err = true;
        }
        return info_list;
    }

    while (TRUE) {
        BOOL bStartsWithDot = (stData.cFileName[0] == '.');
        BOOL bHiddenFile = (stData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);

        //ignore ".", ".." and hidden files.
        if (!bStartsWithDot && !bHiddenFile) {
            file_info info;
            info.is_dir = (stData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
            info.name = stData.cFileName;
            info_list.push_back(info);
        }

        if (!FindNextFileA(hState, &stData)) {
            break;
        }
    }
    FindClose(hState);

    if (err != nullptr) {
        *err = false;
    }
    return info_list;
}

#endif
