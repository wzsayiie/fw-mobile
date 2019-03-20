#include "cqfile.hh"
#include "cqlog.hh"

bool cqIsPathSeperator(char ch) {
    if (cqOnWindows) {
        return ch == '/' || ch == '\\';
    } else /* ON_OSX */ {
        return ch == '/';
    }
}

static string ReadPathItem(const char **reader) {
    while (cqIsPathSeperator(**reader)) {
        ++(*reader);
    }
    if (**reader == '\0') {
        return "";
    }
    
    string item;
    while (!cqIsPathSeperator(**reader) && **reader != '\0') {
        item.append(1, **reader);
        ++(*reader);
    }
    return item;
}

vector<string> cqSplitPath(const string &path) {
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
    if (cqOnOSX && cqIsPathSeperator(path[0])) {
        char seperator[] = { cqPathSeperator, '\0' };
        if (items.size() > 0) {
            items[0] = string(seperator) + items[0];
        } else {
            items.push_back(seperator);
        }
    }
    
    return items;
}

void cqAppendPath(string *path, const string &item) {
    if (path == nullptr || item.empty()) {
        return;
    }
    
    if (!path->empty() && !cqIsPathSeperator(path->back())) {
        path->append(1, cqPathSeperator);
    }
    path->append(item);
}

string cqBaseName(const string &path) {
    vector<string> items = cqSplitPath(path);
    if (items.size() > 0) {
        return items.back();
    } else {
        return "";
    }
}

string cqDirectoryPath(const string &path) {
    vector<string> items = cqSplitPath(path);
    
    if (items.size() > 1) {
        
        string directory;
        for (auto it = items.begin(); it < items.end() - 1; ++it) {
            if (!directory.empty()) {
                directory.append(1, cqPathSeperator);
            }
            directory.append(*it);
        }
        return directory;
        
    } else {
        
        return "";
    }
}

bool cqReadFile(const string &path, vector<char> *content) {
    if (path.empty() || content == nullptr) {
        return false;
    }
    
    FILE *file = fopen(path, "rb");
    if (file == nullptr) {
        return false;
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
    return true;
}

bool cqWriteFile(const string &path, const vector<char> &content) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path, "wb");
    if (file == nullptr) {
        return false;
    }
    fwrite(content.data(), 1, content.size(), file);
    fclose(file);
    return true;
}

static void cqTraverseFile(const string &name, int indent, cqTraverserDelegate *delegate) {
    delegate->traverserGetFile(name, indent);
}

static void cqTraverseDirectory(const string &name, int indent, cqTraverserDelegate *delegate) {
    delegate->traverserGetDirectory(name, indent);
    
    cqChangeDirectory(name);
    vector<string> contents = cqContentsOfDirectory(".");
    for (const string &it : contents) {
        bool isDirectory = false;
        cqFileExistsAtPath(it, &isDirectory);
        if (isDirectory) {
            cqTraverseDirectory(it, indent + 1, delegate);
        } else {
            cqTraverseFile(it, indent + 1, delegate);
        }
    }
    cqChangeDirectory("..");
}

void cqTraverse(const string &path, cqTraverserDelegate *delegate) {
    if (delegate == nullptr) {
        return;
    }
    
    bool isDirectory = false;
    bool fileExists = cqFileExistsAtPath(path, &isDirectory);
    if (!fileExists) {
        return;
    }
    
    string originDirectory = cqGetWorkDirectory();
    string targetParent = cqDirectoryPath(path);
    string targetBase = cqBaseName(path);
    
    cqChangeDirectory(targetParent);
    if (isDirectory) {
        cqTraverseDirectory(targetBase, 0, delegate);
    } else {
        cqTraverseFile(targetBase, 0, delegate);
    }
    cqChangeDirectory(originDirectory);
}
