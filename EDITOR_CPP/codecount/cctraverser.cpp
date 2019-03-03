#include "cctraverser.hh"

CQError CCReadUTF8File(const string &path, const vector<string> &types, vector<char> *out) {
    
    vector<char> content;
    if (CQError error = CQReadFile(path, &content)) {
        return error;
    }
    
    if (!CQUTF8Check(content, nullptr, out)) {
        return CQErrorNotUTF8;
    }
    
    return CQErrorNone;
}

const char *CCFormatted(int number) {
    
    const size_t size = 12;
    static char buffer[size];
    
    if (number >= 1000) {
        snprintf(buffer, size, "%3d,%03d", number / 1000, number % 1000);
    } else {
        snprintf(buffer, size, "%7d", number);
    }
    
    return buffer;
}

int CCPercent(int part, int total) {
    //should be that: 0 <= part <= total
    
    if (total != 0) {
        int centage = part * 100 / total;
        return centage <= 99 ? centage : 99;
    } else {
        return 99;
    }
}

void CCTraverser::count(const vector<string> &paths) {
    
    //begin
    onBegin(&_data);
    
    //stages
    for (const string &it : paths) {
        space_line(1).print("@ %s:", it.c_str());
        space_line(1);
        
        onBeginStage(&_data);
        CQTraverse(it, this);
        onEndStage(&_data);
        
        delete _data.stage;
        _data.stage = nullptr;
    }
    
    //end
    onEnd(&_data);
    
    delete _data.global;
    _data.global = nullptr;
}

void CCTraverser::traverserGetDirectory(const string &name, int indent) {
    onHandleDirectory(&_data, name, indent);
}

void CCTraverser::traverserGetFile(const string &name, int indent) {
    onHandleFile(&_data, name, indent);
}
