#pragma once

#include "cqwin32base.h"

CQ_C_LINK VOID CQLogInfoW (LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...);
CQ_C_LINK VOID CQLogErrorW(LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...);
CQ_C_LINK VOID CQLogInfoA (LPCSTR  pszFile, int nLine, _Printf_format_string_ LPCSTR  pszFormat, ...);
CQ_C_LINK VOID CQLogErrorA(LPCSTR  pszFile, int nLine, _Printf_format_string_ LPCSTR  pszFormat, ...);

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
