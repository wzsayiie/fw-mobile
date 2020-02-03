#pragma once

#include "cqwin32foundationbase.hh"

_CQFOUNDATION_BEGIN_VERSION_NS

CQWSTR CQDocumentDirectoryW();
CQSTR  CQDocumentDirectoryA();
CQWSTR CQTemporaryDirectoryW();
CQSTR  CQTemporaryDirectoryA();

# ifdef UNICODE
#   define CQDocumentDirectory  CQDocumentDirectoryW
#   define CQTemporaryDirectory CQTemporaryDirectoryW
# else
#   define CQDocumentDirectory  CQDocumentDirectoryA
#   define CQTemporaryDirectory CQTemporaryDirectoryA
# endif

BOOL CQDirectoryExistsW(CONST CQWSTR &szPath);
BOOL CQDirectoryExistsA(CONST CQSTR  &szPath);
BOOL CQFileExistsW(CONST CQWSTR &szPath);
BOOL CQFileExistsA(CONST CQSTR  &szPath);
BOOL CQCreateDirectoryW(CONST CQWSTR &szPath, BOOL bIntermediate);
BOOL CQCreateDirectoryA(CONST CQSTR  &szPath, BOOL bIntermediate);
VOID CQRemovePathW(CONST CQWSTR &szPath);
VOID CQRemovePathA(CONST CQSTR  &szPath);

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

CQVEC<CQWSTR> CQSubFilesOfDirectoryW(CONST CQWSTR &szPath, BOOL *pError);
CQVEC<CQSTR>  CQSubFilesOfDirectoryA(CONST CQSTR  &szPath, BOOL *pError);

# ifdef UNICODE
#   define CQSubFilesOfDirectory CQSubFilesOfDirectoryW
# else
#   define CQSubFilesOfDirectory CQSubFilesOfDirectoryA
# endif

_CQFOUNDATION_END_VERSION_NS
