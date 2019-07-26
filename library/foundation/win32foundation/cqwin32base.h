#pragma once

# if    defined(UNICODE) &&  defined(_UNICODE)
# elif !defined(UNICODE) && !defined(_UNICODE)
# else
#   error "macro UNICODE and _UNICODE should be used or not used at the same time"
# endif

#include "cqcbasis.h"
#include <tchar.h>
#include <windows.h>

# ifdef UNICODE
#   define CQ_WIN_FN(NAME) NAME##W
# else
#   define CQ_WIN_FN(NAME) NAME##A
# endif

#define CQ_STR_EMPTY_W(STR) ((BOOL   )cq_u16str_empty((LPCWSTR)STR))
#define CQ_STR_EMPTY_A(STR) ((BOOL   )cq_u8str_empty ((LPCSTR )STR))
#define CQ_STORE_STR_W(STR) ((LPCWSTR)cq_store_u16str((LPCWSTR)STR))
#define CQ_STORE_STR_A(STR) ((LPCSTR )cq_store_u8str ((LPCSTR )STR))
#define CQ_COPY_STR_W( STR) ((LPWSTR )cq_copy_u16str ((LPCWSTR)STR))
#define CQ_COPY_STR_A( STR) ((LPSTR  )cq_copy_u8str  ((LPCSTR )STR))

# ifdef UNICODE
#   define CQ_STR_EMPTY CQ_STR_EMPTY_W
#   define CQ_STORE_STR CQ_STORE_STR_W
#   define CQ_COPY_STR  CQ_COPY_STR_W
# else
#   define CQ_STR_EMPTY CQ_STR_EMPTY_A
#   define CQ_STORE_STR CQ_STORE_STR_A
#   define CQ_COPY_STR  CQ_COPY_STR_A
# endif

#define CQ_ARRAY_LEN(ARR) (sizeof(ARR) / sizeof(*ARR))

//NOTE: the release need to free().
CQ_C_LINK LPWSTR CQWideStringCopyMBS(LPCSTR pszMBS);
CQ_C_LINK LPSTR CQMBStringCopyWS(LPCWSTR pszWS);
