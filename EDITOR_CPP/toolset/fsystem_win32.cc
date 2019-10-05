#ifdef _WIN32

#include "fsystem.hh"
#include "windows.h"

//directory operation:

string getcwd() {
    CHAR szBuffer[256] = "\0";
    GetCurrentDirectoryA(sizeof(szBuffer), szBuffer);
    return szBuffer;
}

bool chdir(const string &dir) {
    return SetCurrentDirectoryA(dir.c_str());
}

//file or directory exists:

bool fexists(const string &path, bool *isdir) {
    DWORD dwAttributes = GetFileAttributesA(path.c_str());
    if (dwAttributes != INVALID_FILE_ATTRIBUTES) {
        if (isdir != nullptr) {
            *isdir = (dwAttributes & FILE_ATTRIBUTE_DIRECTORY);
        }
        return true;
    } else {
        if (isdir != nullptr) {
            *isdir = false;
        }
        return false;
    }
}

//subitems of directory:

vector<fitem> subitems(const string &dir, bool *err) {
    if (dir.empty()) {
        if (err != nullptr) {
            *err = true;
        }
        return vector<fitem>();
    }

    string target = joinpath(dir, "*");
    vector<fitem> items;

    WIN32_FIND_DATAA stData;
    HANDLE hState = FindFirstFileA(target.c_str(), &stData);
    while (hState != INVALID_HANDLE_VALUE) {

        BOOL bStartsWithDot = (stData.cFileName[0] == '.');
        BOOL bHiddenFile = (stData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);

        //ignore ".", ".." and hidden files.
        if (!bStartsWithDot && !bHiddenFile) {
            fitem it;
            it.name = stData.cFileName;
            it.isdir = (stData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
            items.push_back(it);
        }

        if (!FindNextFileA(hState, &stData)) {
            break;
        }
    }
    FindClose(hState);

    if (err != nullptr) {
        *err = false;
    }
    return items;
}

#endif
