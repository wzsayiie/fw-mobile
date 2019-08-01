#pragma once

# if    defined(UNICODE) &&  defined(_UNICODE)
# elif !defined(UNICODE) && !defined(_UNICODE)
# else
#   error "macro UNICODE and _UNICODE should be used or not used at the same time"
# endif

#include "cqcppbasis.hh"
#include <tchar.h>
#include <windows.h>

#include "_CQBASIS_VERSION.h"
_CQBASIS_BEGIN_VERSION_NS

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

CQWSTR CQWStr_Make(CONST WCHAR *lpWStr);
BOOL   CQWStr_Empty(CONST WCHAR *lpWStr);
CQWSTR CQWStr_FromStr(CONST CHAR *pszStr);
CQWSTR CQWStr_FromStr(CONST CQSTR &szStr);
CQWSTR CQWStr_FromU8S(const char *pszStr);
CQWSTR CQWStr_FromU8S(const std::string &szStr);

CQSTR CQStr_Make(CONST CHAR *pszStr);
BOOL  CQStr_Empty(CONST CHAR *pszStr);
CQSTR CQStr_From(CONST WCHAR *pszWStr);
CQSTR CQStr_From(CONST CQWSTR &szWStr);

std::string CQU8Str_From(CONST WCHAR *pszWStr);
std::string CQU8Str_From(CONST CQWSTR &szWStr);

_CQBASIS_END_VERSION_NS
