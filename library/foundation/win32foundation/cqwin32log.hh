#pragma once

#include "cqwin32base.hh"

#include "CQWIN32FOUNDATION_NS.hh"
_CQWIN32FOUNDATION_BEGIN_NS

VOID CQLogInfoW (CONST WCHAR *pszFile, int nLine, _Printf_format_string_ CONST WCHAR *pszFormat, ...);
VOID CQLogErrorW(CONST WCHAR *pszFile, int nLine, _Printf_format_string_ CONST WCHAR *pszFormat, ...);
VOID CQLogInfoA (CONST CHAR  *pszFile, int nLine, _Printf_format_string_ CONST CHAR  *pszFormat, ...);
VOID CQLogErrorA(CONST CHAR  *pszFile, int nLine, _Printf_format_string_ CONST CHAR  *pszFormat, ...);

#define LINFO_W( ...) CQLogInfoW (L"" __FILE__, __LINE__, L"" __VA_ARGS__)
#define LERROR_W(...) CQLogErrorW(L"" __FILE__, __LINE__, L"" __VA_ARGS__)

#define LINFO_A( ...) CQLogInfoA (__FILE__, __LINE__, __VA_ARGS__)
#define LERROR_A(...) CQLogErrorA(__FILE__, __LINE__, __VA_ARGS__)

# ifdef UNICODE
#   define LINFO  LINFO_W
#   define LERROR LERROR_W
# else
#   define LINFO  LINFO_A
#   define LERROR LERROR_A
# endif

_CQWIN32FOUNDATION_END_NS
