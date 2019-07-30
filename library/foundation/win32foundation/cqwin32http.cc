#include "cqwin32http.hh"
#include <winhttp.h>

struct CQHTTP {

    CQWSTR szMethod;
    CQWSTR szUrlString;
    CQMAP<CQWSTR, CQWSTR> mpUrlQuery;
    CQMAP<CQWSTR, CQWSTR> mpRequestHeader;
    CQVEC<BYTE> arRequestBody;
    BOOL bRequestBodyEnd;

    int nResponseCode;
    CQMAP<CQWSTR, CQWSTR> mpResponseHeader;
    CQVEC<BYTE> arResponseBody;
    BOOL bTransferCompleted;
};

CQHTTP *CQHttpOpen()
{
    return new CQHTTP;
}

VOID CQHttpSetMethodW(CQHTTP *lpHttp, CONST CQWSTR &szMethod)
{
    if (lpHttp != NULL)
    {
        lpHttp->szMethod = szMethod;
    }
}

VOID CQHttpSetMethodA(CQHTTP *lpHttp, CONST CQSTR &szMethod)
{
    CQWSTR szMethodW = CQWString::FromStr(szMethod);
    CQHttpSetUrlStringW(lpHttp, szMethodW);
}

VOID CQHttpSetUrlStringW(CQHTTP *lpHttp, CONST CQWSTR &szUrlString)
{
    if (lpHttp != NULL)
    {
        lpHttp->szUrlString = szUrlString;
    }
}

VOID CQHttpSetUrlStringA(CQHTTP *lpHttp, CONST CQSTR &szUrlString)
{
    CQWSTR szUrlStringW = CQWString::FromStr(szUrlString);
    CQHttpSetUrlStringW(lpHttp, szUrlStringW);
}

VOID CQHttpSetUrlQueryW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue)
{
    if (lpHttp != NULL && !szField.empty() && !szValue.empty())
    {
        lpHttp->mpUrlQuery[szField] = szValue;
    }
}

VOID CQHttpSetUrlQueryA(CQHTTP *lpHttp, CONST CQSTR &szField, CONST CQSTR &szValue)
{
    CQWSTR szFieldW = CQWString::FromStr(szField);
    CQWSTR szValueW = CQWString::FromStr(szValue);
    CQHttpSetUrlQueryW(lpHttp, szFieldW, szValueW);
}

VOID CQHttpSetRequestHeaderW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue)
{
    if (lpHttp != NULL && !szField.empty() && !szValue.empty())
    {
        lpHttp->mpRequestHeader[szField] = szValue;
    }
}

VOID CQHttpSetRequestHeaderA(CQHTTP *lpHttp, CONST CQSTR &szField, CONST CQSTR &szValue)
{
    CQWSTR szFieldW = CQWString::FromStr(szField);
    CQWSTR szValueW = CQWString::FromStr(szValue);
    CQHttpSetRequestHeaderW(lpHttp, szFieldW, szValueW);
}

VOID CQHttpSetRequestBody(CQHTTP *lpHttp, BYTE *lpBytes, int nSize, BOOL bEnd)
{
    if (lpHttp != NULL && lpBytes != NULL && nSize > 0 && !lpHttp->bRequestBodyEnd)
    {
        CQVEC<BYTE> *arBody = &lpHttp->arRequestBody;
        arBody->insert(arBody->end(), lpBytes, lpBytes + nSize);
        lpHttp->bRequestBodyEnd = bEnd;
    }
}

BOOL CQHttpConnect(CQHTTP *lpHttp)
{
    return FALSE;
}

int CQHttpGetResponseCode(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        return lpHttp->nResponseCode;
    }
    else
    {
        return 0;
    }
}

VOID CQHttpGetResponseHeaderW(CQHTTP *lpHttp, CQMAP<CQWSTR, CQWSTR> *lpHeader)
{
    if (lpHttp != NULL && lpHeader != NULL)
    {
        *lpHeader = lpHttp->mpResponseHeader;
    }
}

VOID CQHttpGetResponseHeaderA(CQHTTP *lpHttp, CQMAP<CQSTR, CQSTR> *lpHeader)
{
    CQMAP<CQWSTR, CQWSTR> mpHeaderW;
    CQHttpGetResponseHeaderW(lpHttp, &mpHeaderW);

    lpHeader->clear();
    for (auto &cp : mpHeaderW)
    {
        CQSTR szField = CQString::From(cp.first);
        CQSTR szValue = CQString::From(cp.second);
        (*lpHeader)[szField] = szValue;
    }
}

VOID CQHttpGetResponseBody(CQHTTP *lpHttp, CQVEC<BYTE> *lpBody, BOOL *bCompleted)
{
    if (lpHttp != NULL && lpBody != NULL && bCompleted != NULL)
    {
        lpBody->swap(lpHttp->arResponseBody);
        *bCompleted = lpHttp->bTransferCompleted;
    }
}

VOID CQHttpClose(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        delete lpHttp;
    }
}
