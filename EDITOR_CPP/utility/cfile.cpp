#include "cfile.h"

bool CIsPathSeperator(char ch) {
    if (COnWindows) {
        return ch == '/' || ch == '\\';
    } else /* ON_MAC */ {
        return ch == '/';
    }
}

static string ReadPathItem(const char **reader) {
    while (CIsPathSeperator(**reader)) {
        ++(*reader);
    }
    if (**reader == '\0') {
        return "";
    }
    
    string item;
    while (!CIsPathSeperator(**reader) && **reader != '\0') {
        item.append(1, **reader);
        ++(*reader);
    }
    return item;
}

vector<string> CSplitPath(const string &path) {
    if (path.empty()) {
        return vector<string>();
    }
    
    vector<string> items;
    const char *reader = path.c_str();
    while (true) {
        string it = ReadPathItem(&reader);
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
    if (COnOSX && CIsPathSeperator(path[0])) {
        char seperator[] = { CPathSeperator, '\0' };
        if (items.size() > 0) {
            items[0] = string(seperator) + items[0];
        } else {
            items.push_back(seperator);
        }
    }
    
    return items;
}

void CAppendPath(string *path, const string &item) {
    if (path == nullptr || item.empty()) {
        return;
    }
    
    if (!path->empty() && !CIsPathSeperator(path->back())) {
        path->append(1, CPathSeperator);
    }
    path->append(item);
}

string CBaseName(const string &path) {
    vector<string> items = CSplitPath(path);
    if (items.size() > 0) {
        return items.back();
    } else {
        return "";
    }
}

string CDirectoryPath(const string &path) {
    vector<string> items = CSplitPath(path);
    
    if (items.size() > 1) {
        
        string directory;
        for (auto it = items.begin(); it < items.end() - 1; ++it) {
            if (!directory.empty()) {
                directory.append(1, CPathSeperator);
            }
            directory.append(*it);
        }
        return directory;
        
    } else {
        
        return "";
    }
}

CFileError CReadFile(const string &path, vector<char> *content) {
    if (path.empty() || content == nullptr) {
        return CFileError::ParamInvaild;
    }
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return CFileError::OpenFailed;
    }
    
    const size_t bufferSize = 1024;
    char buffer[bufferSize];
    while (true) {
        size_t gotSize = fread(buffer, 1, bufferSize, file);
        content->insert(content->end(), buffer, buffer + gotSize);
        if (gotSize < bufferSize) {
            break;
        }
    }
    
    fclose(file);
    return CFileError::None;
}

CFileError CWriteFile(const string &path, const vector<char> &content) {
    if (path.empty()) {
        return CFileError::ParamInvaild;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return CFileError::OpenFailed;
    }
    fwrite(content.data(), 1, content.size(), file);
    fclose(file);
    return CFileError::None;
}
