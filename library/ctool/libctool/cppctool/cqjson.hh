#pragma once

#include "cqcppbasis.hh"

#include "CQCTOOL_NS.hh"
_CQCTOOL_BEGIN_NS

//
//usage:
//
//| struct oo : cqJson {
//|
//|     cq_json("aa", int32_t) aa;
//|     cq_json("bb", vector<int32_t>) bb;
//|
//|     struct xx : cq::json {
//|         cq_json("ee", int32_t) ee;
//|         cq_json("ff", vector<int32_t>) ff;
//|     };
//|     cq_json("cc", xx) cc;
//|     cq_json("dd", vector<yy>) dd;
//| };
//
//memory dict:
//
//| struct xx : dict {
//|
//|     aa mark;  \ aa entry
//|     aa value; /
//|
//|     bb mark;  \ bb entry
//|     bb value; /
//|
//|     ... ...
//| }
//

namespace _cq_json {
    
    using namespace std;
    
    //dict
    
    struct markcore;
    
    struct dict {
        
        void add(const string &name, size_t offset);
        
        bool read(const char *buffer, size_t *size);
        void write(ostringstream &buffer);
        void write(ostringstream &buffer, bool *newline, int indent);
        void clear();
        
        virtual ~dict();
        
    private:
        
        map<string, size_t> _inoffsets;
        map<string, markcore *> _outmarks;
    };
    
    //mark core:
    
    struct markcore {
        
        markcore(dict *holder, const char *name, size_t offset);
        
        virtual bool read(const char *buffer, size_t *size) = 0;
        virtual void write(ostringstream &buffer) = 0;
        virtual void write(ostringstream &buffer, bool *newline, int indent) = 0;
        virtual void clear() = 0;
        
        virtual ~markcore() = default;
    };
    
    //mark:
    
    inline void output(ostringstream &b, bool    v) {b << v;}
    inline void output(ostringstream &b, int8_t  v) {b << v;}
    inline void output(ostringstream &b, int16_t v) {b << v;}
    inline void output(ostringstream &b, int32_t v) {b << v;}
    inline void output(ostringstream &b, int64_t v) {b << v;}
    inline void output(ostringstream &b, float   v) {b << v;}
    inline void output(ostringstream &b, double  v) {b << v;}
    
    //when string literal as parameter, the parameter will be escaped.
    void output(ostringstream &buffer, const char   *value);
    void output(ostringstream &buffer, const string &value);
    
    inline void output(ostringstream &buffer, dict &value) {
        value.write(buffer);
    }
    
    template<class E> void output(ostringstream &buffer, vector<E> &vec) {
        output(buffer, "[");
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            output(buffer, *it);
            if (it != vec.end() - 1) {
                output(buffer, ",");
            }
        }
        output(buffer, "]");
    }
    
    void space(ostringstream &buffer, int count);
    
    //this function only for pod and std::string type.
    template<class T>
    void _output(ostringstream &buffer, bool *newline, int indent, const T &value) {
        if (*newline) {
            space(buffer, indent);
        }
        output(buffer, value);
        *newline = false;
    }
    
    void output(ostringstream &b, bool *n, int i, bool    v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, int8_t  v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, int16_t v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, int32_t v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, int64_t v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, float   v) {_output(b, n, i, v);}
    void output(ostringstream &b, bool *n, int i, double  v) {_output(b, n, i, v);}
    
    void output(ostringstream &buffer, bool *newline, int indent, const string &value) {
        _output(buffer, newline, indent, value);
    }
    
    inline void output(ostringstream &buffer, bool *newline, int indent, dict &value) {
        value.write(buffer, newline, indent);
    }
    
    template<class E>
    void output(ostringstream &buffer, bool *newline, int indent, vector<E> &vec) {
        //'['
        if (*newline) {
            space(buffer, indent);
        }
        output(buffer, "[\n");
        *newline = true;
        
        //items
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            output(buffer, newline, indent + 1, *it);
            if (it != vec.end() - 1) {
                output(buffer, ",\n");
            } else {
                output(buffer, "\n");
            }
            *newline = true;
        }
        
        //']'
        space(buffer, indent);
        output(buffer, "]");
        *newline = false;
    }
    
    inline void reset(dict &value) {
        value.clear();
    }
    
    template<class T> void reset(T &value) {
        value = T();
    }
    
    template<class E> void reset(vector<E> &value) {
        value.clear();
    }
    
    template<class T> struct mark : markcore {
        
        using markcore::markcore;
        
        bool read(const char *buffer, size_t *size) override {
            return false;
        }
        
        void write(ostringstream &buffer) override {
            output(buffer, value());
        }
        
        void write(ostringstream &buffer, bool *newline, int indent) override {
            output(buffer, newline, indent, value());
        }
        
        void clear() override {
            reset(value());
        }
        
        //mark<T> must be aligned, otherwise "T &value()" can't work.
        static_assert(sizeof(markcore) % sizeof(void *) == 0, "");
        
        T &value() {
            return *(T *)(this + 1);
        }
    };
    
    //entry:
    
    template<class T> struct entry : mark<T> {
        using mark<T>::mark;
        T value;
    };
    
} //namespace _cq_json

struct cqJson : _cq_json::dict {
    
    int32_t fromFile(const std::string &path);
    int32_t fromString(const std::string &str);
    
    int32_t toFile(const std::string &path);
    std::string toString();
    std::string toEasyString();
};

#define _CQ_JSON_NAME  _CQ_JSON_N1(__LINE__)
#define _CQ_JSON_N1(L) _CQ_JSON_N2(L)
#define _CQ_JSON_N2(L) z_json_mark_##L

#define cq_json(N, T)\
/**/    _cq_json::mark<T> _CQ_JSON_NAME =\
/**/    _cq_json::mark<T>(this, N, (size_t)&(((decltype(this))0)->_CQ_JSON_NAME));\
/**/    T

_CQCTOOL_END_NS
