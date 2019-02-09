#include "cqfile.hh"

bool CQIsPathSeperator(char ch) {
    if (CQOnWindows) {
        return ch == '/' || ch == '\\';
    } else /* ON_OSX */ {
        return ch == '/';
    }
}

static string ReadPathItem(const char **reader) {
    while (CQIsPathSeperator(**reader)) {
        ++(*reader);
    }
    if (**reader == '\0') {
        return "";
    }
    
    string item;
    while (!CQIsPathSeperator(**reader) && **reader != '\0') {
        item.append(1, **reader);
        ++(*reader);
    }
    return item;
}

vector<string> CQSplitPath(const string &path) {
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
    if (CQOnOSX && CQIsPathSeperator(path[0])) {
        char seperator[] = { CQPathSeperator, '\0' };
        if (items.size() > 0) {
            items[0] = string(seperator) + items[0];
        } else {
            items.push_back(seperator);
        }
    }
    
    return items;
}

void CQAppendPath(string *path, const string &item) {
    if (path == nullptr || item.empty()) {
        return;
    }
    
    if (!path->empty() && !CQIsPathSeperator(path->back())) {
        path->append(1, CQPathSeperator);
    }
    path->append(item);
}

string CQBaseName(const string &path) {
    vector<string> items = CQSplitPath(path);
    if (items.size() > 0) {
        return items.back();
    } else {
        return "";
    }
}

string CQDirectoryPath(const string &path) {
    vector<string> items = CQSplitPath(path);
    
    if (items.size() > 1) {
        
        string directory;
        for (auto it = items.begin(); it < items.end() - 1; ++it) {
            if (!directory.empty()) {
                directory.append(1, CQPathSeperator);
            }
            directory.append(*it);
        }
        return directory;
        
    } else {
        
        return "";
    }
}

CQFileError CQReadFile(const string &path, vector<char> *content) {
    if (path.empty() || content == nullptr) {
        return CQFileError::ParamInvaild;
    }
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return CQFileError::OpenFailed;
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
    return CQFileError::None;
}

CQFileError CWriteFile(const string &path, const vector<char> &content) {
    if (path.empty()) {
        return CQFileError::ParamInvaild;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return CQFileError::OpenFailed;
    }
    fwrite(content.data(), 1, content.size(), file);
    fclose(file);
    return CQFileError::None;
}
