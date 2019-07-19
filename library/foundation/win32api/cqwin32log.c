#include "cqwin32log.h"
#include <fcntl.h>
#include <io.h>
#include <shlwapi.h>
#include <stdio.h>

static VOID CQChangeModeIfNeeded(int nMode)
{
    if (sizeof(TCHAR) == 2)
    {
        _setmode(_fileno(stdout), nMode);
    }
}

static VOID CQLog(LPCTSTR pszTag, LPCTSTR pszFile, int nLine, LPCTSTR pszFormat, va_list lpArgs)
{
    if (pszFormat == NULL)
    {
        return;
    }
    TCHAR szText[1024 * 4];
    _vstprintf_s(szText, CQ_ARRAY_LEN(szText), pszFormat, lpArgs);

    TCHAR szHeader[128];
    {
        SYSTEMTIME tmNow;
        GetSystemTime(&tmNow);
        DWORD dwThreadId = GetCurrentThreadId();
        _stprintf_s(szHeader, sizeof(szHeader) / sizeof(*szHeader),
            _T("%hd-%02hd-%02hd %02hd:%02hd:%02hd.%03hd [%ld]"),
            tmNow.wYear, tmNow.wMonth, tmNow.wDay,
            tmNow.wHour, tmNow.wMinute, tmNow.wSecond, tmNow.wMilliseconds,
            dwThreadId
        );
    }

    if (!CQ_STR_EMPTY(pszFile) && nLine > 0)
    {
        LPCTSTR pszFileName = PathFindFileName(pszFile);

        CQChangeModeIfNeeded(_O_WTEXT);
        _tprintf(_T("%s %s|%s(%04d)|%s\n"), szHeader, pszTag, pszFileName, nLine, szText);
        CQChangeModeIfNeeded(_O_TEXT);
    }
    else
    {
        CQChangeModeIfNeeded(_O_WTEXT);
        _tprintf(_T("%s %s|%s\n"), szHeader, pszTag, szText);
        CQChangeModeIfNeeded(_O_TEXT);
    }
}

VOID CQ_WIN_FN(CQLogInfo)(LPCTSTR pszFile, int nLine, _Printf_format_string_ LPCTSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLog(_T("I"), pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}

VOID CQ_WIN_FN(CQLogError)(LPCTSTR pszFile, int nLine, _Printf_format_string_ LPCTSTR pszFormat, ...)
{
    va_list lpArgs;
    va_start(lpArgs, pszFormat);
    CQLog(_T("E"), pszFile, nLine, pszFormat, lpArgs);
    va_end(lpArgs);
}
