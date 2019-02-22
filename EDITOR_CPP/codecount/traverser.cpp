#include "traverser.hh"

void Traverser::count(const vector<string> &paths, Traverser *traverser) {
    traverser->_types.clear();
    traverser->_defaultTag.clear();
    
    //1
    I("\n");
    traverser->onStart(&traverser->_types, &traverser->_defaultTag);
    
    //2
    for (const string &it : paths) {
        I("\n@ %s:\n\n", it.c_str());
        traverser->onBeginTask();
        CQTraverse(it, traverser);
        I("\n");
        traverser->onEndTask();
    }
    
    //3
    I("\n");
    traverser->onStop();
    I("\n");
}

string Traverser::traverserGetDefaultTag() {
    return _defaultTag;
}

bool Traverser::traverserFindFile(const string &file, string *outTag) {
    bool isTarget = false;
    for (const string &it : _types) {
        if (file.has_suffix(it)) {
            isTarget = true;
            break;
        }
    }
    
    if (isTarget) {
        onHandleFile(file, outTag);
        return true;
    } else {
        return false;
    }
}

const char *Traverser::ts(int n) {
    const size_t size = 12;
    static char buffer[size];
    
    if (n >= 1000) {
        snprintf(buffer, size, "%3d,%03d", n / 1000, n % 1000);
    } else {
        snprintf(buffer, size, "%7d", n);
    }
    
    return buffer;
}
