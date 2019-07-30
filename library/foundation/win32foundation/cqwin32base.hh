#pragma once

# if    defined(UNICODE) &&  defined(_UNICODE)
# elif !defined(UNICODE) && !defined(_UNICODE)
# else
#   error "macro UNICODE and _UNICODE should be used or not used at the same time"
# endif

#include "cqcppbasis.hh"
#include <tchar.h>
#include <windows.h>

template<class T> using CQFUNC = std::function<T>;

template<class K, class V> using CQMAP = std::map<K, V>;
template<class T> using CQVEC = std::vector<T>;

typedef std::basic_string<WCHAR> CQWSTR;

//NOTE: this's windows multi-byte string, not utf-8 string.
typedef std::basic_string<CHAR> CQSTR;

#ifdef UNICODE
typedef CQWSTR CQTSTR;
#else
typedef CQSTR CQTSTR;
#endif

struct CQWString {
    static CQWSTR Make(CONST WCHAR *lpWStr);
    static BOOL Empty(CONST WCHAR *lpWStr);

    //wide character string from multi-byte string.
    static CQWSTR FromStr(CONST CHAR *pszStr);
    static CQWSTR FromStr(CONST CQSTR &szStr);

    //wide character string from utf-8 string.
    static CQWSTR FromU8S(const char *pszStr);
    static CQWSTR FromU8S(const std::string &szStr);
};

struct CQString {
    static CQSTR Make(CONST CHAR *pszStr);
    static BOOL Empty(CONST CHAR *pszStr);

    //multi-byte string from wide string.
    static CQSTR From(CONST WCHAR *pszWStr);
    static CQSTR From(CONST CQWSTR &szWStr);
};

struct CQU8String {
    //utf-8 string from wide character string.
    static std::string From(CONST WCHAR *pszWStr);
    static std::string From(CONST CQWSTR &szWStr);
};
