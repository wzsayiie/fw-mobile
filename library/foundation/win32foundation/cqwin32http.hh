#pragma once

#include "cqwin32foundationbase.hh"

_CQFOUNDATION_BEGIN_VERSION_NS

struct CQHTTP;

CQHTTP *CQHttpCreate();
VOID CQHttpDestroy(CQHTTP *lpHttp);

VOID CQHttpSetTimeout(CQHTTP *lpHttp, FLOAT fSeconds);

VOID CQHttpSetMethodW(CQHTTP *lpHttp, CONST CQWSTR &szMethod);
VOID CQHttpSetMethodA(CQHTTP *lpHttp, CONST CQSTR  &szMethod);

VOID CQHttpSetUrlStringW(CQHTTP *lpHttp, CONST CQWSTR &szUrlString);
VOID CQHttpSetUrlStringA(CQHTTP *lpHttp, CONST CQSTR  &szUrlString);

//CQHTTP will perform the percent escape on its own.
VOID CQHttpSetUrlQueryW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue);
VOID CQHttpSetUrlQueryA(CQHTTP *lpHttp, CONST CQSTR  &szField, CONST CQSTR  &szValue);

VOID CQHttpSetRequestHeaderW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue);
VOID CQHttpSetRequestHeaderA(CQHTTP *lpHttp, CONST CQSTR  &szField, CONST CQSTR  &szValue);

typedef CQFUNC<int (BYTE *lpBuffer, int nLength)> CQHttpRequestBodyReader;

//if set a RequestBodyReader, the session will use it to get request body,
//else the request body from value set by CQHttpSetRequestBodyData().
VOID CQHttpSetRequestBodyReader(CQHTTP *lpHttp, CQHttpRequestBodyReader fnReader);
VOID CQHttpSetRequestBodyData(CQHTTP *lpHttp, CONST CQVEC<BYTE> &vcData);

VOID CQHttpSyncResume(CQHTTP *lpHttp);

CQWSTR CQHttpErrorW(CQHTTP *lpHttp);
CQSTR  CQHttpErrorA(CQHTTP *lpHttp);

int CQHttpGetResponseCode(CQHTTP *lpHttp);

CQMAP<CQWSTR, CQWSTR> CQHttpGetResponseHeaderW(CQHTTP *lpHttp);
CQMAP<CQSTR , CQSTR > CQHttpGetResponseHeaderA(CQHTTP *lpHttp);

typedef CQFUNC<BOOL (CONST BYTE *lpBytes, int nLength)> CQHttpResponseBodyWriter;

//if set a ResponseBodyWriter, the session will use it to write response body,
//else the response body stored into internal data, which can be get by CQHttpGetResponseBodyData().
VOID CQhttpSetResponseBodyWriter(CQHTTP *lpHttp, CQHttpResponseBodyWriter fnWriter);
CQVEC<BYTE> CQHttpGetResponseBodyData(CQHTTP *lpHttp);

# ifdef UNICODE
#   define CQHttpSetMethod         CQHttpSetMethodW
#   define CQHttpSetUrlString      CQHttpSetUrlStringW
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryW
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderW
#   define CQHttpError             CQHttpErrorW
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderW
# else
#   define CQHttpSetMethod         CQHttpSetMethodA
#   define CQHttpSetUrlString      CQHttpSetUrlStringA
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryA
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderA
#   define CQHttpError             CQHttpErrorA
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderA
# endif

_CQFOUNDATION_END_VERSION_NS
