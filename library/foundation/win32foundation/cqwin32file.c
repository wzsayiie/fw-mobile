#include "cqwin32file.h"
#include <shlobj.h>

LPCTSTR CQ_WIN_FN(CQDocumentDirectory)(VOID)
{
    TCHAR pszPath[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pszPath) == S_OK)
    {
        return CQ_STORE_STR(pszPath);
    }
    else
    {
        return CQ_STORE_STR(NULL);
    }
}

LPCTSTR CQ_WIN_FN(CQCachesDirectory)(VOID)
{
    TCHAR pszPath[MAX_PATH];
    if (GetTempPath(CQ_ARRAY_LEN(pszPath), pszPath) > 0)
    {
        return CQ_STORE_STR(pszPath);
    }
    else
    {
        return CQ_STORE_STR(NULL);
    }
}

LPCTSTR CQ_WIN_FN(CQTemporaryDirectory)(VOID)
{
    return CQCachesDirectory();
}

static BOOL CQDiskItemExists(LPCTSTR pszPath, BOOL* bDirectory)
{
    if (!CQ_STR_EMPTY(pszPath))
    {
        DWORD dwAttributes = GetFileAttributes(pszPath);
        if (dwAttributes != INVALID_FILE_ATTRIBUTES)
        {
            *bDirectory = (dwAttributes & FILE_ATTRIBUTE_DIRECTORY);
            return TRUE;
        }
        else
        {
            *bDirectory = FALSE;
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

BOOL CQ_WIN_FN(CQDirectoryExists)(LPCTSTR pszPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExists(pszPath, &bDirectory);
    return bExists && bDirectory;
}

BOOL CQ_WIN_FN(CQFileExists)(LPCTSTR pszPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExists(pszPath, &bDirectory);
    return bExists && !bDirectory;
}

BOOL CQ_WIN_FN(CQCreateDirectory)(LPCTSTR pszPath, BOOL bIntermediate)
{
    if (CQ_STR_EMPTY(pszPath))
    {
        return FALSE;
    }

    if (bIntermediate)
    {
        //SHCreateDirectory() isn't support relative path.
        if (pszPath[1] != _T(':'))
        {
            TCHAR pszAllPath[MAX_PATH];
            GetCurrentDirectory(CQ_ARRAY_LEN(pszAllPath), pszAllPath);
            _tcscat_s(pszAllPath, CQ_ARRAY_LEN(pszAllPath), _T("\\"));
            _tcscat_s(pszAllPath, CQ_ARRAY_LEN(pszAllPath), pszPath);
            return SHCreateDirectoryEx(NULL, pszAllPath, NULL) == ERROR_SUCCESS;
        }
        else
        {
            return SHCreateDirectoryEx(NULL, pszPath, NULL) == ERROR_SUCCESS;
        }
    }
    else
    {
        return CreateDirectory(pszPath, NULL);
    }
}

VOID CQ_WIN_FN(CQRemovePath)(LPCTSTR pszPath)
{
    if (CQ_STR_EMPTY(pszPath))
    {
        return;
    }

    SHFILEOPSTRUCT stOperation;
    memset(&stOperation, 0, sizeof(stOperation));
    stOperation.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
    stOperation.pFrom = pszPath;
    stOperation.pTo = NULL;
    stOperation.wFunc = FO_DELETE;

    SHFileOperation(&stOperation);
}
