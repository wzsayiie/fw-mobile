#include "cqwin32file.hh"
#include <shlobj.h>

_CQWIN32FOUNDATION_BEGIN_NS

CQWSTR CQDocumentDirectoryW()
{
    WCHAR szPath[MAX_PATH];
    HRESULT retResult = SHGetFolderPathW(NULL, CSIDL_PERSONAL, NULL, 0, szPath);
    
    if (retResult == S_OK)
    {
        return szPath;
    }
    else
    {
        return CQWSTR();
    }
}

CQSTR CQDocumentDirectoryA()
{
    CQWSTR szPath = CQDocumentDirectoryW();
    return CQStr::From(szPath);
}

CQWSTR CQCachesDirectoryW()
{
    WCHAR szPath[MAX_PATH];
    DWORD dwLength = GetTempPathW(MAX_PATH, szPath);

    if (dwLength > 0)
    {
        return szPath;
    }
    else
    {
        return CQWSTR();
    }
}

CQSTR CQCachesDirectoryA()
{
    CQWSTR szPath = CQCachesDirectoryW();
    return CQStr::From(szPath);
}

CQWSTR CQTemporaryDirectoryW()
{
    return CQCachesDirectoryW();
}

CQSTR CQTemporaryDirectoryA()
{
    return CQCachesDirectoryA();
}

static BOOL CQDiskItemExistsW(CONST CQWSTR &szPath, BOOL *bDirectory)
{
    DWORD dwAttributes = GetFileAttributesW(szPath.c_str());
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

BOOL CQDirectoryExistsW(CONST CQWSTR &szPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExistsW(szPath, &bDirectory);
    return bExists && bDirectory;
}

BOOL CQDirectoryExistsA(CONST CQSTR &szPath)
{
    CQWSTR szPathW = CQWStr::FromStr(szPath);
    return CQDirectoryExistsW(szPathW);
}

BOOL CQFileExistsW(CONST CQWSTR &szPath)
{
    BOOL bDirectory = FALSE;
    BOOL bExists = CQDiskItemExistsW(szPath, &bDirectory);
    return bExists && !bDirectory;
}

BOOL CQFileExistsA(CONST CQSTR &szPath)
{
    CQWSTR szPathW = CQWStr::FromStr(szPath);
    return CQFileExistsW(szPathW);
}

BOOL CQCreateDirectoryW(CONST CQWSTR &szPath, BOOL bIntermediate)
{
    if (bIntermediate)
    {
        //SHCreateDirectory() isn't support relative path.
        if (szPath.size() >= 2 && szPath[1] != L':')
        {
            CQWSTR szAllPath;
            szAllPath.resize(MAX_PATH);
            GetCurrentDirectoryW(MAX_PATH, (LPWSTR)szAllPath.c_str());
            szAllPath += L"\\";
            szAllPath += szPath;

            int nError = SHCreateDirectoryExW(NULL, szAllPath.c_str(), NULL);
            return nError == ERROR_SUCCESS;
        }
        else
        {
            int nError = SHCreateDirectoryExW(NULL, szPath.c_str(), NULL);
            return nError == ERROR_SUCCESS;
        }
    }
    else
    {
        return CreateDirectoryW(szPath.c_str(), NULL);
    }
}

BOOL CQCreateDirectoryA(CONST CQSTR &szPath, BOOL bIntermediate)
{
    CQWSTR szPathW = CQWStr::FromStr(szPath);
    return CQCreateDirectoryW(szPathW, bIntermediate);
}

VOID CQRemovePathW(CONST CQWSTR &szPath)
{
    //SHFILEOPSTRUCT.pFrom need double null terminating.
    size_t zPathSize = szPath.size();
    CQVEC<WCHAR> szFromPathes(zPathSize + 2);
    wcscpy(szFromPathes.data(), szPath.c_str());
    szFromPathes[zPathSize + 1] = L'\0';

    SHFILEOPSTRUCTW stOperation;
    memset(&stOperation, 0, sizeof(stOperation));
    stOperation.wFunc = FO_DELETE;
    stOperation.pFrom = szFromPathes.data();
    stOperation.pTo = NULL;
    stOperation.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
    SHFileOperationW(&stOperation);
}

VOID CQRemovePathA(CONST CQSTR &szPath)
{
    CQWSTR szPathW = CQWStr::FromStr(szPath);
    CQRemovePathW(szPathW);
}

_CQWIN32FOUNDATION_END_NS
