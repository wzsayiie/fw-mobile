#include "cqjson.hh"
#include "cqdata.hh"
#include <cmath>
#include <sstream>

//parse string:

static void skip_blank(const char *&p) {
    while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
        p += 1;
    }
}

static cq::value parse_null(const char *&p, bool &e) {
    skip_blank(p);

    if (!strncmp(p, "null", 4) && !isalpha(p[4])) {
        p += 4;
        return nullptr;
    }
    
    e = true;
    return nullptr;
}

static cq::value parse_bool(const char *&p, bool &e) {
    skip_blank(p);

    if (!strncmp(p, "true", 4) && !isalpha(p[4])) {
        p += 4;
        return true;
    }
    if (!strncmp(p, "false", 5) && !isalpha(p[5])) {
        p += 5;
        return false;
    }
    
    e = true;
    return nullptr;
}

static cq::value parse_str(const char *&p, bool &e) {
    //1. first '"':
    skip_blank(p);
    if (*p != '"') {
        e = true;
        return nullptr;
    }
    p += 1;
    
    //2. content:
    std::string v;
    while (*p != '\0' && *p != '"') {
        if (*p == '\\') {
            //NOTE: "uXXXX" is not supported.
            switch (p[1]) {
                break; case '"' : v.append(1, '"' ); p += 2;
                break; case '\\': v.append(1, '\\'); p += 2;
                break; case '/' : v.append(1, '/' ); p += 2;
                break; case 'b' : v.append(1, '\b'); p += 2;
                break; case 'f' : v.append(1, '\f'); p += 2;
                break; case 'n' : v.append(1, '\n'); p += 2;
                break; case 'r' : v.append(1, '\r'); p += 2;
                break; case 't' : v.append(1, '\t'); p += 2;
                default: {
                    e = true;
                    return nullptr;
                }
            }
        } else {
            v.append(1, *p);
            p += 1;
        }
    }

    //3. last '"':
    if (*p == '"') {
        p += 1;
        return v;
    }

    e = true;
    return nullptr;
}

//declare.
static cq::value parse_value(const char *&p, bool &e);

static cq::value parse_vector(const char *&p, bool &e) {
    //1. first '[':
    skip_blank(p);
    if (*p != '[') {
        e = true;
        return nullptr;
    }
    p += 1;

    //2. items:
    std::vector<cq::value> v;

    //is empty vector.
    skip_blank(p);
    if (*p == ']') {
        p += 1;
        return v;
    }

    while (true) {
        cq::value i = parse_value(p, e);
        if (e) {
            return nullptr;
        }
        v.push_back(i);

        skip_blank(p);
        if (*p == ']') {
            break;
        } else if (*p == ',') {
            p += 1;
        } else {
            e = true;
            return nullptr;
        }
    }

    //3. last ']':
    if (*p == ']') {
        p += 1;
        return v;
    }

    e = true;
    return nullptr;
}

static cq::value parse_str_map(const char *&p, bool &e) {
    //1. first '{':
    skip_blank(p);
    if (*p != '{') {
        e = true;
        return nullptr;
    }
    p += 1;

    //2. pairs:
    std::map<std::string, cq::value> m;

    //is empty map.
    skip_blank(p);
    if (*p == '}') {
        p += 1;
        return m;
    }
    
    while (true) {
        std::string k = parse_str(p, e).get_str();
        if (e) {
            return nullptr;
        }
        if (k.empty()) {
            e = true;
            return nullptr;
        }

        skip_blank(p);
        if (*p != ':') {
            e = true;
            return nullptr;
        }
        p += 1;

        cq::value v = parse_value(p, e);
        if (e) {
            return nullptr;
        }
        m[k] = v;

        skip_blank(p);
        if (*p == '}') {
            break;
        } else if (*p == ',') {
            p += 1;
        } else {
            e = true;
            return nullptr;
        }
    }

    //3. last '}':
    if (*p == '}') {
        p += 1;
        return m;
    }

    e = true;
    return nullptr;
}

//like this number "-12.34".
//if get a integer return true, else if a double return false.
static bool parse_num(const char *&p, int64_t *i, double *f, bool &e) {

    //NOTE: do not skip blank.
    //parse_e_num() will call this function two times continuously.

    bool neg = false;
    if (*p == '+') {
        neg = false;
        p += 1;
    } else if (*p == '-') {
        neg = true;
        p += 1;
    }

    //1. integer part:
    if (!isdigit(*p)) {
        e = true;
        return true;
    }

    *i = 0;
    *f = 0;
    while (isdigit(*p)) {
        *i = (*i) * 10 + (*p - '0');
        *f = (*f) * 10 + (*p - '0');
        p += 1;
    }

    //2. '.':
    if (*p != '.') {
        if (neg) {
            *i = -(*i);
        }
        return true;
    }
    p += 1;

    //3. decimal part:
    if (!isdigit(*p)) {
        e = true;
        return true;
    }

    double w = 0.1;
    while (isdigit(*p)) {
        *f = (*f) + (*p - '0') * w;
        w /= 10.0;
        p += 1;
    }

    if (neg) {
        *f = -(*f);
    }
    return false;
}

//lile this number "-12.34e5.6"
static cq::value parse_e_num(const char *&p, bool &e) {
    skip_blank(p);

    //base:
    int64_t ib = 0;
    double  fb = 0;
    bool is_ib = parse_num(p, &ib, &fb, e);

    if (e) {
        return nullptr;
    }

    //'e':
    if (*p != 'e' && *p != 'E') {
        if (is_ib) {
            return ib;
        } else {
            return fb;
        }
    }
    p += 1;

    //exponent:
    int64_t ie = 0;
    double  fe = 0;
    bool is_ie = parse_num(p, &ie, &fe, e);

    if (e) {
        return nullptr;
    }

    if (is_ib) {
        fb = ib;
    }
    if (is_ie) {
        fe = ie;
    }
    return pow(fb, fe);
}

static cq::value parse_value(const char *&p, bool &e) {
    skip_blank(p);
    switch (*p) {
        break; case 'n': return parse_null   (p, e);
        break; case 't': return parse_bool   (p, e);
        break; case 'f': return parse_bool   (p, e);
        break; case '"': return parse_str    (p, e);
        break; case '[': return parse_vector (p, e);
        break; case '{': return parse_str_map(p, e);
        default /*...*/: return parse_e_num  (p, e);
    }
}

cq::value cqJson::parseString(const std::string &string, int *position) {

    //in general the json root should be a object(std::map<std::string, value>),
    //but no required here. even so only one value is still parsed.
    const char *ptr = string.c_str();
    bool error = false;
    cq::value value = parse_value(ptr, error);

    if (error) {
        if (position != nullptr) {
            *position = (int)(ptr - string.c_str());
        }
        return nullptr;
    } else {
        if (position != nullptr) {
            *position = INT_MAX;
        }
        return value;
    }
}

//file operate:

cq::value cqJson::parseFile(const std::string &path, int *position) {
    //1. read file:
    std::vector<uint8_t> data;
    if (!cqData::readFromFile(path, &data)) {
        if (position != nullptr) {
            *position = -1;
        }
        return nullptr;
    }
    
    //2. parse json:
    std::string string;
    string.assign(data.data(), data.data() + data.size());
    
    return cqJson::parseString(string, position);
}

bool cqJson::writeFile(const std::string &path, const cq::value &value) {
    std::string json = cqJson::terseJson(value);
    
    std::vector<uint8_t> data;
    data.assign(json.data(), json.data() + json.size());
    
    return cqData::writeToFile(path, data);
}

//terse json:

inline void append(std::stringstream &s, std::nullptr_t) { s << "null"; }
inline void append(std::stringstream &s, bool    _value) { s << _value; }
inline void append(std::stringstream &s, int64_t _value) { s << _value; }
inline void append(std::stringstream &s, double  _value) { s << _value; }

static void append(std::stringstream &s, const std::string &v) {
    s << '"';
    for (char c : v) {
        switch (c) {
            break; case '\"': s << "\\\"";
            break; case '\\': s << "\\\\";
            break; case '/' : s << "\\/";
            break; case '\b': s << "\\b";
            break; case '\f': s << "\\f";
            break; case '\n': s << "\\n";
            break; case '\r': s << "\\r";
            break; case '\t': s << "\\t";
            default/*other*/: s << c;
        }
    }
    s << '"';
}

//declare.
static void append(std::stringstream &s, const cq::value &v);

static void append(std::stringstream &s, const std::vector<cq::value> &v) {
    s << '[';
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (i != v.begin()) {
            s << ',';
        }
        append(s, *i);
    }
    s << ']';
}

template<class T> void append(std::stringstream &s, const std::map<T, cq::value> &v) {
    s << '{';
    for (auto p = v.begin(); p != v.end(); ++p) {
        if (p != v.begin()) {
            s << ',';
        }
        append(s, p->first);
        s << ':';
        append(s, p->second);
    }
    s << '}';
}

static void append(std::stringstream &s, const cq::value &v) {
    switch (v.type()) {
        break; case cq::type_null   : append(s, nullptr        );
        break; case cq::type_bool   : append(s, v.get_bool   ());
        break; case cq::type_int64  : append(s, v.get_int64  ());
        break; case cq::type_double : append(s, v.get_double ());
        break; case cq::type_str    : append(s, v.get_str    ());
        break; case cq::type_vector : append(s, v.get_vector ());
        break; case cq::type_str_map: append(s, v.get_str_map());
        break; case cq::type_int_map: append(s, v.get_int_map());
        default:;
    }
}

std::string cqJson::terseJson(const cq::value &value) {
    std::stringstream stream;
    stream << std::boolalpha;
    append(stream, value);
    return stream.str();
}

//formatted json:

static void indent(std::stringstream &s, bool need, int n) {
    while (need && n-- > 0) {
        //..."1234"
        s << "    ";
    }
}

template<class T> void append(std::stringstream &s, const T &v, bool newline, int n) {
    indent(s, newline, n);
    append(s, v);
}

//declare.
static void append(std::stringstream &s, const cq::value &v, bool newline, int n);

static void append(
    std::stringstream &s, const std::vector<cq::value> &v, bool newline, int n)
{
    indent(s, newline, n);

    //the vector is empty.
    if (v.empty()) {
        s << "[]";
        return;
    }

    //the vector is no empty.
    s << "[\n";
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (i != v.begin()) {
            s << ",\n";
        }
        append(s, *i, true, n + 1);
    }
    s << "\n";
    indent(s, true, n);
    s << "]";
}

template<class T> void append(
    std::stringstream &s, const std::map<T, cq::value> &v, bool newline, int n)
{
    indent(s, newline, n);

    //the map is empty.
    if (v.empty()) {
        s << "{}";
        return;
    }

    //the map is not empty.
    s << "{\n";
    for (auto p = v.begin(); p != v.end(); ++p) {
        if (p != v.begin()) {
            s << ",\n";
        }
        append(s, p->first, true, n + 1);
        s << ": ";
        append(s, p->second, false, n + 1);
    }
    s << "\n";
    indent(s, true, n);
    s << "}";
}

static void append(std::stringstream &s, const cq::value &v, bool newline, int n) {
    switch (v.type()) {
        break; case cq::type_null   : append(s, nullptr        , newline, n);
        break; case cq::type_bool   : append(s, v.get_bool   (), newline, n);
        break; case cq::type_int64  : append(s, v.get_int64  (), newline, n);
        break; case cq::type_double : append(s, v.get_double (), newline, n);
        break; case cq::type_str    : append(s, v.get_str    (), newline, n);
        break; case cq::type_vector : append(s, v.get_vector (), newline, n);
        break; case cq::type_str_map: append(s, v.get_str_map(), newline, n);
        break; case cq::type_int_map: append(s, v.get_int_map(), newline, n);
        default:;
    }
}

std::string cqJson::formattedJson(const cq::value &value) {
    std::stringstream stream;
    stream << std::boolalpha;
    append(stream, value, false, 0);
    return stream.str();
}
