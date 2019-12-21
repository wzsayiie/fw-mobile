#include "cqvalue.hh"

using namespace cq;

typedef std::string                  str_t    ;
typedef std::vector<value>           vector_t ;
typedef std::map<std::string, value> str_map_t;
typedef std::map<int64_t, value>     int_map_t;

inline str_t     &str    (void *p) { return *(str_t     *)p; }
inline vector_t  &vector (void *p) { return *(vector_t  *)p; }
inline str_map_t &str_map(void *p) { return *(str_map_t *)p; }
inline int_map_t &int_map(void *p) { return *(int_map_t *)p; }

static void convert(_value_dat *dat, value_type type) {
    if (dat->type == type) {
        return;
    }

    //delete old data:
    switch (dat->type) {
        break; case type_str    : delete &str    (dat->a_ptr);
        break; case type_vector : delete &vector (dat->a_ptr);
        break; case type_str_map: delete &str_map(dat->a_ptr);
        break; case type_int_map: delete &int_map(dat->a_ptr);
        default:;
    }

    //assign new data:
    dat->type = type;
    switch (type) {
        break; case type_null   : dat->a_int64  = 0;
        break; case type_bool   : dat->a_bool   = false;
        break; case type_int64  : dat->a_int64  = 0;
        break; case type_double : dat->a_double = 0.0;
        break; case type_str    : dat->a_ptr = new str_t;
        break; case type_vector : dat->a_ptr = new vector_t;
        break; case type_str_map: dat->a_ptr = new str_map_t;
        break; case type_int_map: dat->a_ptr = new int_map_t;
        default:;
    }
}

//construct:

value::value()               { *this = nullptr; }
value::value(std::nullptr_t) { *this = nullptr; }

value::value(bool    v) { *this = v; }
value::value(int8_t  v) { *this = v; }
value::value(int16_t v) { *this = v; }
value::value(int32_t v) { *this = v; }
value::value(int64_t v) { *this = v; }
value::value(float   v) { *this = v; }
value::value(double  v) { *this = v; }

value::value(const char      *v) { *this = v; }
value::value(const str_t     &v) { *this = v; }
value::value(const vector_t  &v) { *this = v; }
value::value(const str_map_t &v) { *this = v; }
value::value(const int_map_t &v) { *this = v; }
value::value(const value     &v) { *this = v; }

//getter:

value_type value::type() const {
    return dat.type;
}

bool value::get_bool() const {
    switch (dat.type) {
        break; case type_null   : return false;
        break; case type_bool   : return dat.a_bool;
        break; case type_int64  : return dat.a_int64 != 0;
        break; case type_double : return cq_dbl_equal(dat.a_double, 0.0);
        break; case type_str    : return !str    (dat.a_ptr).empty();
        break; case type_vector : return !vector (dat.a_ptr).empty();
        break; case type_str_map: return !str_map(dat.a_ptr).empty();
        break; case type_int_map: return !int_map(dat.a_ptr).empty();
        default /* unexpected */: return false;
    }
}

int8_t  value::get_int8 () const { return (int8_t )get_int64(); }
int16_t value::get_int16() const { return (int16_t)get_int64(); }
int32_t value::get_int32() const { return (int32_t)get_int64(); }

int64_t value::get_int64() const {
    switch (dat.type) {
        break; case type_null   : return 0;
        break; case type_bool   : return dat.a_bool ? 1 : 0;
        break; case type_int64  : return dat.a_int64;
        break; case type_double : return (int64_t)dat.a_double;
        break; case type_str    : return atoll(str(dat.a_ptr).c_str());
        break; case type_vector : return 0;
        break; case type_str_map: return 0;
        break; case type_int_map: return 0;
        default /* unexpected */: return 0;
    }
}

float value::get_float() const {
    return (float)get_double();
}

double value::get_double() const {
    switch (dat.type) {
        break; case type_null   : return 0.0;
        break; case type_bool   : return dat.a_bool ? 1.0 : 0.0;
        break; case type_int64  : return (double)dat.a_int64;
        break; case type_double : return dat.a_double;
        break; case type_str    : return atof(str(dat.a_ptr).c_str());
        break; case type_vector : return 0.0;
        break; case type_str_map: return 0.0;
        break; case type_int_map: return 0.0;
        default /* unexpected */: return 0.0;
    }
}

str_t value::get_str() const {
    switch (dat.type) {
        break; case type_null   : return "null";
        break; case type_bool   : return dat.a_bool ? "true" : "false";
        break; case type_int64  : return std::to_string(dat.a_int64);
        break; case type_double : return std::to_string(dat.a_double);
        break; case type_str    : return str(dat.a_ptr);
        break; case type_vector : return "[...]";
        break; case type_str_map: return "{...}";
        break; case type_int_map: return "{...}";
        default /* unexpected */: return "null";
    }
}

vector_t value::get_vector() const {
    if (dat.type == type_vector) {
        return vector(dat.a_ptr);
    } else {
        return vector_t();
    }
}

str_map_t value::get_str_map() const {
    if (dat.type == type_int_map) {

        //int_map_t can be cast to str_map_t.
        const int_map_t &from = int_map(dat.a_ptr);

        str_map_t to;
        for (const auto &cp : from) {
            to[std::to_string(cp.first)] = cp.second;
        }
        return to;

    } else if (dat.type == type_str_map) {
        return str_map(dat.a_ptr);
    } else {
        return str_map_t();
    }
}

int_map_t value::get_int_map() const {
    if (dat.type == type_int_map) {
        return int_map(dat.a_ptr);
    } else {
        return int_map_t();
    }
}

//setter:

const value &value::operator=(std::nullptr_t) {
    convert(&dat, type_null);
    return *this;
}

const value &value::operator=(bool v) {
    convert(&dat, type_bool);
    dat.a_bool = v;
    return *this;
}

const value &value::operator=(int8_t  v) { return *this = (int64_t)v; }
const value &value::operator=(int16_t v) { return *this = (int64_t)v; }
const value &value::operator=(int32_t v) { return *this = (int64_t)v; }

const value &value::operator=(int64_t v) {
    convert(&dat, type_int64);
    dat.a_int64 = v;
    return *this;
}

const value &value::operator=(float v) {
    *this = (double)v;
    return *this;
}

const value &value::operator=(double v) {
    convert(&dat, type_double);
    dat.a_double = v;
    return *this;
}

const value &value::operator=(const char *v) {
    if (v != nullptr) {
        convert(&dat, type_str);
        str(dat.a_ptr) = v;
    } else {
        convert(&dat, type_null);
    }
    return *this;
}

const value &value::operator=(const str_t &v) {
    convert(&dat, type_str);
    str(dat.a_ptr) = v;
    return *this;
}

const value &value::operator=(const vector_t &v) {
    convert(&dat, type_vector);
    vector(dat.a_ptr) = v;
    return *this;
}

const value &value::operator=(const str_map_t &v) {
    convert(&dat, type_str_map);
    str_map(dat.a_ptr) = v;
    return *this;
}

const value &value::operator=(const int_map_t &v) {
    convert(&dat, type_int_map);
    int_map(dat.a_ptr) = v;
    return *this;
}

const value &value::operator=(const value &v) {
    convert(&dat, v.dat.type);
    switch (dat.type) {
        break; case type_null   : dat.a_int64  = v.dat.a_int64;
        break; case type_bool   : dat.a_bool   = v.dat.a_bool;
        break; case type_int64  : dat.a_int64  = v.dat.a_int64;
        break; case type_double : dat.a_double = v.dat.a_double;
        break; case type_str    : str    (dat.a_ptr) = str    (v.dat.a_ptr);
        break; case type_vector : vector (dat.a_ptr) = vector (v.dat.a_ptr);
        break; case type_str_map: str_map(dat.a_ptr) = str_map(v.dat.a_ptr);
        break; case type_int_map: int_map(dat.a_ptr) = int_map(v.dat.a_ptr);
        default /* unexpected */: dat.a_int64 = v.dat.a_int64;
    }
    return *this;
}

vector_t &value::as_vector() {
    convert(&dat, type_vector);
    return vector(dat.a_ptr);
}

str_map_t &value::as_str_map() {
    convert(&dat, type_str_map);
    return str_map(dat.a_ptr);
}

int_map_t &value::as_int_map() {
    convert(&dat, type_int_map);
    return int_map(dat.a_ptr);
}

value &value::operator[](const std::string &k) {
    convert(&dat, type_str_map);
    return str_map(dat.a_ptr)[k];
}

//destruct:

value::~value() {
    convert(&dat, type_null);
}
