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

# ifdef UNICODE
#   define CQ_STR_EMPTY(STR) ((LPCWSTR)cq_u16str_empty((LPCWSTR)STR))
#   define CQ_STORE_STR(STR) ((LPCWSTR)cq_store_u16str((LPCWSTR)STR))
# else
#   define CQ_STR_EMPTY(STR) ((LPCSTR)cq_u8str_empty((LPCSTR)STR))
#   define CQ_STORE_STR(STR) ((LPCSTR)cq_store_u8str((LPCSTR)STR))
# endif

#define CQ_ARRAY_LEN(ARR) (sizeof(ARR) / sizeof(*ARR))
