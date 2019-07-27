#pragma once

# if    defined(UNICODE) &&  defined(_UNICODE)
# elif !defined(UNICODE) && !defined(_UNICODE)
# else
#   error "macro UNICODE and _UNICODE should be used or not used at the same time"
# endif

#include "cqcbasis.h"
#include <tchar.h>
#include <windows.h>

//NOTE:
//memory layout of null-terminated multibyte string and null-terminated utf-8 string are same,
//but they have different meanings.

#define cq_wstr_empty cq_u16str_empty
#define cq_str_empty  cq_u8str_empty
#define cq_copy_wstr  cq_copy_u16str
#define cq_copy_str   cq_copy_u8str
#define cq_store_wstr cq_store_u16str
#define cq_store_str  cq_store_u8str
#define cq_alloc_wstr cq_alloc_u16str
#define cq_alloc_str  cq_alloc_u8str
#define cq_wsfrom8s   cq_u16sfrom8s
#define cq_u8sfromws  cq_u8sfrom16s

# ifdef UNICODE
#   define cq_tstr_empty cq_wstr_empty
#   define cq_copy_tstr  cq_copy_wstr
#   define cq_store_tstr cq_store_wstr
#   define cq_alloc_tstr cq_alloc_wstr
# else
#   define cq_tstr_empty cq_str_empty
#   define cq_copy_tstr  cq_copy_str
#   define cq_store_tstr cq_store_str
#   define cq_alloc_tstr cq_alloc_str
# endif

CQ_C_LINK LPCWSTR CQWideStringFromMBS(LPCSTR pszMBS);
CQ_C_LINK LPCSTR CQMBStringFormWS(LPCWSTR pszWS);
