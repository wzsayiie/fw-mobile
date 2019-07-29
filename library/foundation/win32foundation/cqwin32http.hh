#pragma once

#include "cqwin32base.hh"

struct CQHTTP;

CQHTTP *CQHttpOpen();

VOID CQHttpSetMethodW(CQHTTP *lpHttp, CONST CQWSTR &szMethod);
VOID CQHttpSetMethodA(CQHTTP *lpHttp, CONST CQSTR  &szMethod);

VOID CQHttpSetUrlStringW(CQHTTP *lpHttp, CONST CQWSTR &szUrlString);
VOID CQHttpSetUrlStringA(CQHTTP *lpHttp, CONST CQSTR  &szUrlString);

//CQHTTP will perform the percent escape on its own.
VOID CQHttpSetUrlQueryW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue);
VOID CQHttpSetUrlQueryA(CQHTTP *lpHttp, CONST CQSTR  &szField, CONST CQSTR  &szValue);

VOID CQHttpSetRequestHeaderW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue);
VOID CQHttpSetRequestHeaderA(CQHTTP *lpHttp, CONST CQSTR  &szField, CONST CQSTR  &szValue);

//write request body. bEnd specifies write data finished or not.
//NOTE: this function could be call both before and after CQHttpConnect().
VOID CQHttpSetRequestBody(CQHTTP *lpHttp, BYTE *lpBytes, int nSize, BOOL bEnd);

//if connect failed, return FASLE.
//NOTE: even fails, also need call CQHttpClose() to clean.
BOOL CQHttpConnect(CQHTTP *lpHttp);

int CQHttpGetResponseCode(CQHTTP *lpHttp);

VOID CQHttpGetResponseHeaderW(CQHTTP *lpHttp, CQMAP<CQWSTR, CQWSTR> *lpHeader);
VOID CQHttpGetResponseHeaderA(CQHTTP *lpHttp, CQMAP<CQSTR , CQSTR > *lpHeader);

VOID CQHttpGetResponseBody(CQHTTP *lpHttp, CQVEC<BYTE> *lpBody, BOOL *bCompleted);

VOID CQHttpClose(CQHTTP *lpHttp);

# ifdef UNICODE
#   define CQHttpSetMethod         CQHttpSetMethodW
#   define CQHttpSetUrlString      CQHttpSetUrlStringW
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryW
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderW
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderW
# else
#   define CQHttpSetMethod         CQHttpSetMethodA
#   define CQHttpSetUrlString      CQHttpSetUrlStringA
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryA
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderA
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderA
# endif
