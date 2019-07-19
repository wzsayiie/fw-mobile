#pragma once

#include "cqwin32base.h"

CQ_C_LINK VOID CQSetLogTextModeW(VOID);
CQ_C_LINK VOID CQSetLogTextModeA(VOID);

# ifdef UNICODE
#   define CQSetLogTextMode CQSetLogTextModeW
# else
#   define CQSetLogTextMode CQSetLogTextModeA
# endif

CQ_C_LINK VOID CQLogInfoW (LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...);
CQ_C_LINK VOID CQLogErrorW(LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...);
CQ_C_LINK VOID CQLogInfoA (LPCSTR  pszFile, int nLine, _Printf_format_string_ LPCSTR  pszFormat, ...);
CQ_C_LINK VOID CQLogErrorA(LPCSTR  pszFile, int nLine, _Printf_format_string_ LPCSTR  pszFormat, ...);

# ifdef UNICODE
#   define CQLogInfo  CQLogInfoW
#   define CQLogError CQLogErrorW
# else
#   define CQLogInfo  CQLogInfoA
#   define CQLogError CQLogErrorA
# endif

#define INF(...) CQLogInfo (_T(__FILE__), __LINE__, __VA_ARGS__)
#define ERR(...) CQLogError(_T(__FILE__), __LINE__, __VA_ARGS__)
