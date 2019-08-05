#include "cqwin32http.hh"
#include <winhttp.h>

_CQFOUNDATION_BEGIN_VERSION_NS

struct CQHTTP {

    FLOAT fTimeoutSeconds;
    CQWSTR szMethod;
    CQWSTR szUrlString;
    CQMAP<CQWSTR, CQWSTR> mpUrlQuery;
    CQMAP<CQWSTR, CQWSTR> mpRequestHeader;
    CQHttpRequestBodyReader fnRequestBodyReader;
    CQVEC<BYTE> vcRequestBodyData;

    CQWSTR szError;
    int nResponseCode = 0;
    CQMAP<CQWSTR, CQWSTR> mpResponseHeader;
    CQHttpResponseBodyWriter fnResponseBodyWriter;
    CQVEC<BYTE> vcResponseBodyData;
};

CQHTTP *CQHttpCreate()
{
    return new CQHTTP;
}

VOID CQHttpDestroy(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        delete lpHttp;
    }
}

VOID CQHttpSetTimeout(CQHTTP *lpHttp, FLOAT fSeconds)
{
    if (lpHttp != NULL)
    {
        lpHttp->fTimeoutSeconds = fSeconds;
    }
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
    CQWSTR szMethodW = CQWStr_FromStr(szMethod);
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
    CQWSTR szUrlStringW = CQWStr_FromStr(szUrlString);
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
    CQWSTR szFieldW = CQWStr_FromStr(szField);
    CQWSTR szValueW = CQWStr_FromStr(szValue);
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
    CQWSTR szFieldW = CQWStr_FromStr(szField);
    CQWSTR szValueW = CQWStr_FromStr(szValue);
    CQHttpSetRequestHeaderW(lpHttp, szFieldW, szValueW);
}

VOID CQHttpSetRequestBodyReader(CQHTTP *lpHttp, CQHttpRequestBodyReader fnReader)
{
    if (lpHttp != NULL)
    {
        lpHttp->fnRequestBodyReader = fnReader;
    }
}

VOID CQHttpSetRequestBodyData(CQHTTP *lpHttp, CONST CQVEC<BYTE> &vcData)
{
    if (lpHttp != NULL)
    {
        lpHttp->vcRequestBodyData = vcData;
    }
}

VOID CQHttpSyncResume(CQHTTP *lpHttp)
{
    //todo
}

CQWSTR CQHttpErrorW(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        return lpHttp->szError;
    }
    else
    {
        return CQWSTR();
    }
}

CQSTR CQHttpErrorA(CQHTTP *lpHttp)
{
    CQWSTR szErrorW = CQHttpErrorW(lpHttp);
    return CQStr_From(szErrorW);
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

CQMAP<CQWSTR, CQWSTR> CQHttpGetResponseHeaderW(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        return lpHttp->mpResponseHeader;
    }
    else
    {
        return CQMAP<CQWSTR, CQWSTR>();
    }
}

CQMAP<CQSTR, CQSTR> CQHttpGetResponseHeaderA(CQHTTP *lpHttp)
{
    CQMAP<CQWSTR, CQWSTR> mpHeaderW = CQHttpGetResponseHeaderW(lpHttp);

    CQMAP<CQSTR, CQSTR> mpHeaderA;
    for (auto &cp : mpHeaderW)
    {
        CQSTR szField = CQStr_From(cp.first);
        CQSTR szValue = CQStr_From(cp.second);
        mpHeaderA[szField] = szValue;
    }
    return mpHeaderA;
}

VOID CQhttpSetResponseBodyWriter(CQHTTP *lpHttp, CQHttpResponseBodyWriter writer)
{
    if (lpHttp != NULL)
    {
        lpHttp->fnResponseBodyWriter = writer;
    }
}

CQVEC<BYTE> CQHttpGetResponseBodyData(CQHTTP *lpHttp)
{
    if (lpHttp != NULL)
    {
        return lpHttp->vcResponseBodyData;
    }
    else
    {
        return CQVEC<BYTE>();
    }
}

_CQFOUNDATION_END_VERSION_NS
