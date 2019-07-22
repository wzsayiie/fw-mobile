#pragma once

#include "cqwin32base.h"

CQ_C_LINK LPCWSTR CQDocumentDirectoryW(VOID);
CQ_C_LINK LPCSTR  CQDocumentDirectoryA(VOID);
CQ_C_LINK LPCWSTR CQCachesDirectoryW(VOID);
CQ_C_LINK LPCSTR  CQCachesDirectoryA(VOID);
CQ_C_LINK LPCWSTR CQTemporaryDirectoryW(VOID);
CQ_C_LINK LPCSTR  CQTemporaryDirectoryA(VOID);

# ifdef UNICODE
#   define CQDocumentDirectory  CQDocumentDirectoryW
#   define CQCachesDirectory    CQCachesDirectoryW
#   define CQTemporaryDirectory CQTemporaryDirectoryW
# else
#   define CQDocumentDirectory  CQDocumentDirectoryA
#   define CQCachesDirectory    CQCachesDirectoryA
#   define CQTemporaryDirectory CQTemporaryDirectoryA
# endif

CQ_C_LINK BOOL CQDirectoryExistsW(LPCWSTR pszPath);
CQ_C_LINK BOOL CQDirectoryExistsA(LPCSTR  pszPath);
CQ_C_LINK BOOL CQFileExistsW(LPCWSTR pszPath);
CQ_C_LINK BOOL CQFileExistsA(LPCSTR  pszPath);
CQ_C_LINK BOOL CQCreateDirectoryW(LPCWSTR pszPath, BOOL bIntermediate);
CQ_C_LINK BOOL CQCreateDirectoryA(LPCSTR  pszPath, BOOL bIntermediate);
CQ_C_LINK VOID CQRemovePathW(LPCWSTR pszPath);
CQ_C_LINK VOID CQRemovePathA(LPCSTR  pszPath);

# ifdef UNICODE
#   define CQDirectoryExists CQDirectoryExistsW
#   define CQFileExists      CQFileExistsW
#   define CQCreateDirectory CQCreateDirectoryW
#   define CQRemovePath      CQRemovePathW
# else
#   define CQDirectoryExists CQDirectoryExistsA
#   define CQFileExists      CQFileExistsA
#   define CQCreateDirectory CQCreateDirectoryA
#   define CQRemovePath      CQRemovePathA
# endif
