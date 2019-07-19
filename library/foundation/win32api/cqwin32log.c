#include "cqwin32log.h"
#include <fcntl.h>
#include <io.h>
#include <shlwapi.h>
#include <stdio.h>

VOID CQ_WIN_FN(CQSetLogTextMode)(VOID)
{
    //if the print function does not match the text mode,
    //a system exception will be stared.
    if (sizeof(TCHAR) == 2)
    {
        _setmode(_fileno(stdout), _O_WTEXT);
    }
    else
    {
        _setmode(_fileno(stdout), _O_TEXT);
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
        _tprintf(_T("%s %s|%s(%04d)|%s\n"), szHeader, pszTag, pszFileName, nLine, szText);
    }
    else
    {
        _tprintf(_T("%s %s|%s\n"), szHeader, pszTag, szText);
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
