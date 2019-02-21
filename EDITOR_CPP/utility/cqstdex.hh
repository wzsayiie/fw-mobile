#pragma once

#include <string>
#include <vector>
#include <map>

# ifdef __OBJC__
#   import <Foundation/Foundation.h>
# endif

using std::vector;
using std::map;

struct string : std::string {
    
    string();
    string(const std::string &that);
    string(const char *that);
    
    const string &operator=(const char *that);
    operator const char *() const;
    
#ifdef __OBJC__
    string(NSString *that);
    const string &operator=(NSString *that);
    operator NSString *() const;
#endif
    
    //NOTE: if *this == prefix(or suffix), return false
    bool has_prefix(const string &prefix) const;
    bool has_suffix(const string &suffix) const;
    
private:
    
    static const char *non_null(const char *value);
};

struct object {
    virtual ~object() = default;
};
