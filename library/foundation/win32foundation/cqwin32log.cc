﻿#include "cqwin32log.hh"
#include <fcntl.h>
#include <io.h>
#include <shlwapi.h>
#include <stdio.h>

_CQFOUNDATION_BEGIN_VERSION_NS

VOID CQLogW(CONST WCHAR *pszTag, CONST WCHAR *pszFile, int nLine, CONST WCHAR *pszFormat, va_list lpArgs)
{
    int _ignored = _setmode(_fileno(stdout), _O_WTEXT);

    if (!CQWStr_Empty(pszFile) && nLine > 0)
    {
        LPCWSTR pszFileName = PathFindFileNameW(pszFile);
        wprintf(L"%s|%s(%04d)|", pszTag, pszFileName, nLine);
    }
    else
    {
        wprintf(L"%s|", pszTag);
    }

    vwprintf(pszFormat, lpArgs);
    wprintf(L"\n");

    _ignored = _setmode(_fileno(stdout), _O_TEXT);
}

VOID CQLogInfoW(CONST WCHAR *pszFile, int nLine, _Printf_format_string_ CONST WCHAR *pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogW(L"I", pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQLogErrorW(CONST WCHAR *pszFile, int nLine, _Printf_format_string_ CONST WCHAR *pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogW(L"E", pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQLogA(CONST CHAR *pszTag, CONST CHAR *pszFile, int nLine, CONST CHAR *pszFormat, va_list lpArgs)
{
    CONST DWORD dwMessage = 1024 * 4;
    CHAR szMessage[dwMessage];
    vsprintf_s(szMessage, dwMessage, pszFormat, lpArgs);

    if (!CQStr_Empty(pszFile) && nLine > 0)
    {
        LPCSTR pszFileName = PathFindFileNameA(pszFile);
        printf("%s|%s(%04d)|%s\n", pszTag, pszFileName, nLine, szMessage);
    }
    else
    {
        printf("%s|%s\n", pszTag, szMessage);
    }
}

VOID CQLogInfoA(CONST CHAR *pszFile, int nLine, _Printf_format_string_ CONST CHAR *pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogA("I", pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQLogErrorA(CONST CHAR *pszFile, int nLine, _Printf_format_string_ CONST CHAR *pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogA("E", pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}

_CQFOUNDATION_END_VERSION_NS
