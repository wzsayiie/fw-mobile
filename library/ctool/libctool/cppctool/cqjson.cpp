#include "cqjson.hh"

using namespace _cq_json;
using namespace std;

static map<string, markcore *> inmarks(void *base, const map<string, size_t> &offsets) {
    map<string, markcore *> marks;
    for (auto &cp : offsets) {
        marks[cp.first] = (markcore *)((char *)base + cp.second);
    }
    return marks;
}

void _cq_json::dict::add(const string &name, size_t offset) {
    _inoffsets[name] = offset;
}

bool _cq_json::dict::read(const char *buffer, size_t *size) {
    return false;
}

void _cq_json::dict::write(ostringstream &buffer) {
    //write inner and outter entries.
    map<string, markcore *> marks = inmarks(this, _inoffsets);
    marks.insert(_outmarks.begin(), _outmarks.end());
    
    output(buffer, "{");
    size_t count = 0;
    for (auto &it : marks) {
        output(buffer, it.first);
        output(buffer, ":");
        it.second->write(buffer);
        if (count++ < marks.size() - 1) {
            output(buffer, ",");
        }
    }
    output(buffer, "}");
}

void _cq_json::dict::write(ostringstream &buffer, bool *newline, int indent) {
    //write inner and outter entries.
    map<string, markcore *> marks = inmarks(this, _inoffsets);
    marks.insert(_outmarks.begin(), _outmarks.end());
    
    //'{'
    if (*newline) {
        space(buffer, indent);
    }
    output(buffer, "{\n");
    *newline = true;
    
    //entries
    size_t count = 0;
    for (auto &it : marks) {
        
        output(buffer, newline, indent + 1, it.first);
        output(buffer, ": ");
        *newline = false;
        
        it.second->write(buffer, newline, indent + 1);
        if (count++ < marks.size() - 1) {
            output(buffer, ",\n");
        } else {
            output(buffer, "\n");
        }
        *newline = true;
    }
    
    //'}'
    space(buffer, indent);
    output(buffer, "}");
    *newline = false;
}

void _cq_json::dict::clear() {
    //only clear inner marks
    map<string, markcore *> marks = inmarks(this, _inoffsets);
    for (auto &cp : marks) {
        cp.second->clear();
    }
}

_cq_json::dict::~dict() {
    for (auto &cp : _outmarks) {
        delete cp.second;
    }
}

_cq_json::markcore::markcore(dict *holder, const char *name, size_t offset) {
    if (holder && name && *name) {
        holder->add(name, offset);
    }
}

void _cq_json::output(ostringstream &buffer, const char *value) {
    buffer << value;
}

void _cq_json::output(ostringstream &buffer, const string &value) {
    
    //currently '\uXXXX' supported.
    
    buffer << '\"';
    for (char it : value) {
        switch (it) {
        case '"' : buffer << "\\\""; break;
        case '\\': buffer << "\\\\"; break;
        case '/' : buffer << "/"   ; break;
        case '\b': buffer << "\\b" ; break;
        case '\f': buffer << "\\f" ; break;
        case '\n': buffer << "\\n" ; break;
        case '\r': buffer << "\\r" ; break;
        case '\t': buffer << "\\t" ; break;
        default  : buffer << it    ;
        };
    }
    buffer << '\"';
}

void _cq_json::space(ostringstream &buffer, int count) {
    while (count-- > 0) {
        buffer << "\x20\x20\x20\x20";
    }
}

int32_t cqJson::fromFile(const string &path) {
    return 0;
}

int32_t cqJson::fromString(const string &str) {
    return 0;
}

int32_t cqJson::toFile(const string &path) {
    if (path.empty()) {
        return 1;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return 2;
    }
    
    string content = toString();
    fwrite(content.data(), 1, content.size(), file);
    fclose(file);
    return 0;
}

string cqJson::toString() {
    ostringstream buffer;
    buffer << boolalpha;
    write(buffer);
    return buffer.str();
}

string cqJson::toEasyString() {
    ostringstream buffer;
    
    bool newline = false;
    buffer << boolalpha;
    write(buffer, &newline, 0);
    
    return buffer.str();
}
