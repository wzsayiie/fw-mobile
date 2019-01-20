#pragma once

#include <iostream>
#include "types.h"

struct log_once {
    
    //is there start of one line.
    //in functions 'put()', check this flag for doing right things,
    //and resets it when returns.
    bool _newline;
    
    template<class T> log_once(const string &tag, T value) {
        if (!tag.empty()) {
            std::cout << "<" << tag << ">";
            _newline = false;
        } else {
            _newline = true;
        }
        this->put(value, 0);
    }
    
    template<class T> log_once &operator/(T value) {
        this->put(value, 0);
        return *this;
    }
    
    void space(int n) {
        if (_newline) {
            std::cout.width(n * 4);
            std::cout << "";
        } else {
            std::cout << " ";
        }
    }
    
    template<class T> void put(T value, int indent) {
        this->space(indent);
        std::cout << value;
        _newline = false;
    }
    
    void put(const char *value, int indent) {
        if (indent == 0) {
            //if indent is 0, think of it as literal value
            if (value != nullptr) {
                if (!_newline && !ispunct(*value) && !isspace(*value)) {
                    this->space(0);
                }
                std::cout << value;
                _newline = false;
            }
        } else {
            this->space(indent);
            if (value != nullptr) {
                std::cout << "\"" << value << "\"";
            } else {
                std::cout << "0x0";
            }
            _newline = false;
        }
    }
    
    void put(const string &value, int indent) {
        this->space(indent);
        std::cout << "\"" << value << "\"";
        _newline = false;
    }
    
    template<class T> void put(const vector<T> &value, int indent) {
        //1 print "["
        this->space(indent);
        if (value.empty()) {
            std::cout << "[]";
            _newline = false;
            return;
        } else {
            std::cout << "[\n";
            _newline = true;
        }
        
        //2 print items
        for (auto it : value) {
            this->put(it, indent + 1);
            if (!_newline) {
                std::cout << "\n";
                _newline = true;
            }
        }
        
        //3 print "]"
        this->space(indent);
        std::cout << "]\n";
        _newline = true;
    }
    
    template<class K, class V> void put(const map<K, V> &value, int indent) {
        //1 print "{"
        this->space(indent);
        if (value.empty()) {
            std::cout << "{}";
            _newline = false;
            return;
        } else {
            std::cout << "{\n";
            _newline = true;
        }
        
        //2 print items
        for (auto it : value) {
            this->put(it.first, indent + 1);
            std::cout << " =";
            _newline = false;
            this->put(it.second, indent + 1);
            if (!_newline) {
                std::cout << "\n";
                _newline = true;
            }
        }
        
        //3 print "]"
        this->space(indent);
        std::cout << "}\n";
        _newline = true;
    }
    
    ~log_once() {
        std::cout << std::endl;
    }
};

struct logger {
    logger(const string &tag): tag(tag) {
        std::cout.setf(std::ios_base::boolalpha);
    }
    template<class T> log_once operator/(T value) {
        return log_once(tag, value);
    }
    const string tag;
};

extern logger cinfo;
extern logger cerr;
extern logger cprint;
