#include "cqwin32log.h"
#include <fcntl.h>
#include <io.h>
#include <shlwapi.h>
#include <stdio.h>

static VOID CQLogW(LPCWSTR pszFile, int nLine, LPCWSTR pszTag, LPCWSTR pszText)
{
    WCHAR szHeader[128];
    {
        SYSTEMTIME tmNow;
        GetSystemTime(&tmNow);
        DWORD dwThreadId = GetCurrentThreadId();
        swprintf_s(szHeader, CQ_ARRAY_LEN(szHeader),
            L"%hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd [%ld]",
            tmNow.wYear, tmNow.wMonth, tmNow.wDay,
            tmNow.wHour, tmNow.wMinute, tmNow.wSecond, tmNow.wMilliseconds,
            dwThreadId
        );
    }

    _setmode(_fileno(stdout), _O_WTEXT);
    if (!CQ_STR_EMPTY_W(pszFile) && nLine > 0)
    {
        LPCWSTR pszFileName = PathFindFileName(pszFile);
        wprintf(L"%s %s|%s(%04d)|%s\n", szHeader, pszTag, pszFileName, nLine, pszText);
    }
    else
    {
        wprintf(L"%s %s|%s\n", szHeader, pszTag, pszText);
    }
    _setmode(_fileno(stdout), _O_TEXT);
}

static VOID CQLogvW(LPCWSTR pszFile, int nLine, LPCWSTR pszTag, LPCWSTR pszFormat, va_list lpArgs)
{
    if (CQ_STR_EMPTY_W(pszFormat))
    {
        return;
    }

    WCHAR szText[1024 * 4];
    vswprintf_s(szText, CQ_ARRAY_LEN(szText), pszFormat, lpArgs);
    CQLogW(pszFile, nLine, pszTag, szText);
}

VOID CQLogInfoW(LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogvW(pszFile, nLine, L"I", pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQLogErrorW(LPCWSTR pszFile, int nLine, _Printf_format_string_ LPCWSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogvW(pszFile, nLine, L"E", pszFormat, lpArgs);
    va_end(lpArgs);
}

static VOID CQLogvA(LPCSTR pszFile, int nLine, LPCSTR pszTag, LPCSTR pszFormat, va_list lpArgs)
{
    if (CQ_STR_EMPTY(pszFormat))
    {
        return;
    }

    CHAR szText[1024 * 4];
    vsprintf_s(szText, CQ_ARRAY_LEN(szText), pszFormat, lpArgs);

    LPWSTR a = CQWideStringCopyMBS(pszFile);
    LPWSTR b = CQWideStringCopyMBS(pszTag);
    LPWSTR c = CQWideStringCopyMBS(szText);
    CQLogW(a, nLine, b, c);
    free(a);
    free(b);
    free(c);
}

VOID CQLogInfoA(LPCSTR pszFile, int nLine, _Printf_format_string_ LPCSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogvA(pszFile, nLine, "I", pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQLogErrorA(LPCSTR pszFile, int nLine, _Printf_format_string_ LPCSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLogvA(pszFile, nLine, "E", pszFormat, lpArgs);
    va_end(lpArgs);
}
