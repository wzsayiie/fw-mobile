#pragma once

# if    defined(UNICODE) &&  defined(_UNICODE)
# elif !defined(UNICODE) && !defined(_UNICODE)
# else
#   error "macro UNICODE and _UNICODE should be used or not used at the same time"
# endif

#include "cqcppbasis.hh"
#include <tchar.h>
#include <windows.h>

//NOTE:
//memory layout of null-terminated multibyte string and null-terminated utf-8 string are same,
//but they have different meanings.
inline BOOL    cq_wstr_empty(LPCWSTR s) { return (BOOL   )cq_u16str_empty((const char16_t *)s); }
inline BOOL    cq_str_empty (LPCSTR  s) { return (BOOL   )cq_u8str_empty ((const char     *)s); }
inline LPWSTR  cq_copy_wstr (LPCWSTR s) { return (LPWSTR )cq_copy_u16str ((const char16_t *)s); }
inline LPSTR   cq_copy_str  (LPCSTR  s) { return (LPSTR  )cq_copy_u8str  ((const char     *)s); }
inline LPCWSTR cq_store_wstr(LPCWSTR s) { return (LPCWSTR)cq_store_u16str((const char16_t *)s); }
inline LPCSTR  cq_store_str (LPCSTR  s) { return (LPCSTR )cq_store_u8str ((const char     *)s); }
inline LPCWSTR cq_wsfrom8s  (LPCSTR  s) { return (LPCWSTR)cq_u16sfrom8s  ((const char     *)s); }
inline LPCSTR  cq_u8sfromws (LPCWSTR s) { return (LPCSTR )cq_u8sfrom16s  ((const char16_t *)s); }

LPCWSTR cq_wsfrommbs(LPCSTR mbs);
LPCSTR  cq_mbsfromws(LPCWSTR ws);

# ifdef UNICODE
#   define cq_tstr_empty cq_wstr_empty
#   define cq_copy_tstr  cq_copy_wstr
#   define cq_store_tstr cq_store_wstr
# else
#   define cq_tstr_empty cq_str_empty
#   define cq_copy_tstr  cq_copy_str
#   define cq_store_tstr cq_store_str
# endif

template<class T> using CQFUNC = std::function<T>;

template<class K, class V> using CQMAP = std::map<K, V>;
template<class T> using CQVEC = std::vector<T>;

typedef std::basic_string<WCHAR> CQWSTR;
typedef std::basic_string<CHAR> CQSTR;
