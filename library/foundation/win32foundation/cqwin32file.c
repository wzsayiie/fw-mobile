#include "cqwin32file.h"
#include <shlobj.h>

LPCWSTR CQDocumentDirectoryW(VOID)
{
    WCHAR pszPath[MAX_PATH];
    if (SHGetFolderPathW(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pszPath) == S_OK)
    {
        return CQ_STORE_STR_W(pszPath);
    }
    else
    {
        return CQ_STORE_STR_W(NULL);
    }
}

LPCSTR CQDocumentDirectoryA(VOID)
{
    LPCWSTR x = CQDocumentDirectoryW();
    LPSTR   y = CQMBStringCopyWS(x);
    LPCSTR  z = CQ_STORE_STR_A(y);

    free(y);
    return z;
}

LPCWSTR CQCachesDirectoryW(VOID)
{
    WCHAR pszPath[MAX_PATH];
    if (GetTempPathW(CQ_ARRAY_LEN(pszPath), pszPath) > 0)
    {
        return CQ_STORE_STR_W(pszPath);
    }
    else
    {
        return CQ_STORE_STR_W(NULL);
    }
}

LPCSTR CQCachesDirectoryA(VOID)
{
    LPCWSTR x = CQCachesDirectoryW();
    LPSTR   y = CQMBStringCopyWS(x);
    LPCSTR  z = CQ_STORE_STR_A(y);

    free(y);
    return z;
}

LPCWSTR CQTemporaryDirectoryW(VOID)
{
    return CQCachesDirectoryW();
}

LPCSTR CQTemporaryDirectoryA(VOID)
{
    return CQCachesDirectoryA();
}

static BOOL CQDiskItemExistsW(LPCWSTR pszPath, BOOL* bDirectory)
{
    if (!CQ_STR_EMPTY_W(pszPath))
    {
        DWORD dwAttributes = GetFileAttributesW(pszPath);
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

BOOL CQDirectoryExistsW(LPCWSTR pszPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExistsW(pszPath, &bDirectory);
    return bExists && bDirectory;
}

BOOL CQDirectoryExistsA(LPCSTR pszPath)
{
    LPWSTR a = CQWideStringCopyMBS(pszPath);
    BOOL   x = CQDirectoryExistsW(a);

    free(a);
    return x;
}

BOOL CQFileExistsW(LPCWSTR pszPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExistsW(pszPath, &bDirectory);
    return bExists && !bDirectory;
}

BOOL CQFileExistsA(LPCSTR pszPath)
{
    LPWSTR a = CQWideStringCopyMBS(pszPath);
    BOOL   x = CQFileExistsW(a);

    free(a);
    return x;
}

BOOL CQCreateDirectoryW(LPCWSTR pszPath, BOOL bIntermediate)
{
    if (CQ_STR_EMPTY_W(pszPath))
    {
        return FALSE;
    }

    if (bIntermediate)
    {
        //SHCreateDirectory() isn't support relative path.
        if (pszPath[1] != L':')
        {
            WCHAR pszAllPath[MAX_PATH];
            GetCurrentDirectoryW(CQ_ARRAY_LEN(pszAllPath), pszAllPath);
            wcscat_s(pszAllPath, CQ_ARRAY_LEN(pszAllPath), L"\\");
            wcscat_s(pszAllPath, CQ_ARRAY_LEN(pszAllPath), pszPath);
            return SHCreateDirectoryExW(NULL, pszAllPath, NULL) == ERROR_SUCCESS;
        }
        else
        {
            return SHCreateDirectoryExW(NULL, pszPath, NULL) == ERROR_SUCCESS;
        }
    }
    else
    {
        return CreateDirectoryW(pszPath, NULL);
    }
}

BOOL CQCreateDirectoryA(LPCSTR pszPath, BOOL bIntermediate)
{
    LPWSTR a = CQWideStringCopyMBS(pszPath);
    BOOL x = CQCreateDirectoryW(a, bIntermediate);

    free(a);
    return x;
}

VOID CQRemovePathW(LPCWSTR pszPath)
{
    if (CQ_STR_EMPTY_W(pszPath))
    {
        return;
    }

    //SHFILEOPSTRUCT.pFrom need double null terminating.
    size_t nPath = wcslen(pszPath);
    LPWSTR pszFromPath = malloc((nPath + 2) * sizeof(WCHAR));
    wcscpy(pszFromPath, pszPath);
    pszFromPath[nPath + 1] = L'\0';

    SHFILEOPSTRUCTW stOperation;
    memset(&stOperation, 0, sizeof(stOperation));
    stOperation.pFrom = pszFromPath;
    stOperation.pTo = NULL;
    stOperation.wFunc = FO_DELETE;
    stOperation.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
    SHFileOperation(&stOperation);

    free(pszFromPath);
}

VOID CQRemovePathA(LPCSTR pszPath)
{
    LPWSTR a = CQWideStringCopyMBS(pszPath);
    CQRemovePathW(a);
    free(a);
}
