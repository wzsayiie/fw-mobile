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
        swprintf_s(szHeader, cq_array_count(szHeader),
            L"%hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd [%ld]",
            tmNow.wYear, tmNow.wMonth, tmNow.wDay,
            tmNow.wHour, tmNow.wMinute, tmNow.wSecond, tmNow.wMilliseconds,
            dwThreadId
        );
    }

    _setmode(_fileno(stdout), _O_WTEXT);
    if (!cq_wstr_empty(pszFile) && nLine > 0)
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

//wide character version:

static VOID CQLogvW(LPCWSTR pszFile, int nLine, LPCWSTR pszTag, LPCWSTR pszFormat, va_list lpArgs)
{
    if (cq_wstr_empty(pszFormat))
    {
        return;
    }

    WCHAR szText[1024 * 4];
    vswprintf_s(szText, cq_array_count(szText), pszFormat, lpArgs);
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

//narrow character version:

static VOID CQLogvA(LPCSTR pszFile, int nLine, LPCSTR pszTag, LPCSTR pszFormat, va_list lpArgs)
{
    if (cq_str_empty(pszFormat))
    {
        return;
    }

    CHAR szText[1024 * 4];
    vsprintf_s(szText, cq_array_count(szText), pszFormat, lpArgs);

    cq_auto_pool
    {
        LPCWSTR pszFileW = cq_auto_wstr(CQWideStringFromMBS(pszFile));
        LPCWSTR pszTagW  = cq_auto_wstr(CQWideStringFromMBS(pszTag));
        LPCWSTR pszTextW = cq_auto_wstr(CQWideStringFromMBS(szText));

        CQLogW(pszFileW, nLine, pszTagW, pszTextW);
    }
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
