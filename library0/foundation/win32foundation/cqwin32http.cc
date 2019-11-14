#include "cqwin32http.hh"
#include <winhttp.h>

_CQFOUNDATION_BEGIN_VERSION_NS

struct CQHTTP {

    FLOAT fTimeoutSeconds = 0;
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

static CQWSTR UrlEscape(CONST CQWSTR &szSRC)
{
    CQWSTR szDST;
    for (WCHAR ch : szSRC)
    {
        switch (ch)
        {
        case L' ' : szDST.append(L"%20"); break;
        case L'!' : szDST.append(L"%21"); break;
        case L'"' : szDST.append(L"%22"); break;
        case L'#' : szDST.append(L"%23"); break;
        case L'$' : szDST.append(L"%24"); break;
        case L'%' : szDST.append(L"%25"); break;
        case L'&' : szDST.append(L"%26"); break;
        case L'\'': szDST.append(L"%27"); break;
        case L'(' : szDST.append(L"%28"); break;
        case L')' : szDST.append(L"%29"); break;
        case L'*' : szDST.append(L"%2A"); break;
        case L'+' : szDST.append(L"%2B"); break;
        case L',' : szDST.append(L"%2C"); break;
        case L'/' : szDST.append(L"%2F"); break;
        case L':' : szDST.append(L"%3A"); break;
        case L';' : szDST.append(L"%3B"); break;
        case L'<' : szDST.append(L"%3C"); break;
        case L'=' : szDST.append(L"%3D"); break;
        case L'>' : szDST.append(L"%3E"); break;
        case L'?' : szDST.append(L"%3F"); break;
        case L'@' : szDST.append(L"%40"); break;
        case L'[' : szDST.append(L"%5B"); break;
        case L'\\': szDST.append(L"%5C"); break;
        case L']' : szDST.append(L"%5D"); break;
        case L'|' : szDST.append(L"%7C"); break;
        default: szDST.append(1, ch);
        }
    }

    return szDST;
}

VOID CQHttpSetUrlQueryW(CQHTTP *lpHttp, CONST CQWSTR &szField, CONST CQWSTR &szValue)
{
    if (lpHttp != NULL && !szField.empty() && !szValue.empty())
    {
        CQWSTR szEscapedField = UrlEscape(szField);
        CQWSTR szEscapedValue = UrlEscape(szValue);
        lpHttp->mpUrlQuery[szEscapedField] = szEscapedValue;
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

struct URLSTRUCT {
    BOOL bHttps = FALSE;
    CQWSTR szHost;
    WORD wPort = 0;
    CQWSTR szPath;
};

static URLSTRUCT UrlStruct(CONST CQWSTR &szUrlString, CONST CQMAP<CQWSTR, CQWSTR> &mpQuery)
{
    URLSTRUCT stStruct;
    CONST WCHAR *lpRead = szUrlString.c_str();

    //if https or not:
    if (_wcsnicmp(lpRead, L"https://", 8) == 0)
    {
        stStruct.bHttps = TRUE;
        lpRead += 8;
    }
    else if (_wcsnicmp(lpRead, L"http://", 7) == 0)
    {
        lpRead += 7;
    }

    //get host string:
    while (*lpRead != L'\0' && *lpRead != L'/' && *lpRead != ':')
    {
        stStruct.szHost.append(1, *lpRead);
        lpRead += 1;
    }

    //get port:
    if (*lpRead == ':')
    {
        lpRead += 1;
        while (L'0' <= *lpRead && *lpRead <= L'9')
        {
            stStruct.wPort = stStruct.wPort * 10 + (*lpRead - L'0');
            lpRead += 1;
        }
    }
    else
    {
        stStruct.wPort = stStruct.bHttps ? 443 : 80;
    }

    //get path:
    while (*lpRead == L'/')
    {
        lpRead += 1;
    }
    stStruct.szPath = lpRead;

    for (auto it = mpQuery.begin(); it != mpQuery.end(); ++it)
    {
        if (it == mpQuery.begin())
        {
            if (!stStruct.szPath.empty())
            {
                stStruct.szPath.append(L"?");
            }
        }
        else
        {
            stStruct.szPath.append(L"&");
        }

        stStruct.szPath.append(it->first);
        stStruct.szPath.append(L"=");
        stStruct.szPath.append(it->second);
    }

    return stStruct;
}

static HINTERNET OpenHttpSession(CQHTTP *lpHttp)
{
    HINTERNET hSession = WinHttpOpen(
        L"CQ HTTP (WinHttp implementation)",
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0);

    if (hSession != NULL && lpHttp->fTimeoutSeconds > 0)
    {
        int nMS = (int)(1000 * lpHttp->fTimeoutSeconds);
        WinHttpSetTimeouts(hSession, nMS, nMS, nMS, nMS);
    }
    
    return hSession;
}

static HINTERNET OpenHttpConnect(HINTERNET hSession, CQHTTP *lpHttp, CONST URLSTRUCT &stUrlStruct)
{
    return WinHttpConnect(hSession, stUrlStruct.szHost.c_str(), stUrlStruct.wPort, 0);
}

static HINTERNET OpenHttpRequest(HINTERNET hConnect, CQHTTP *lpHttp, CONST URLSTRUCT &stUrlStruct)
{
    CQWSTR szMethod;
    if (!lpHttp->szMethod.empty())
    {
        szMethod = lpHttp->szMethod;
        std::transform(szMethod.begin(), szMethod.end(), szMethod.begin(), ::toupper);
    }
    else
    {
        szMethod = L"GET";
    }

    DWORD dwRequestFlag = 0;
    if (stUrlStruct.bHttps)
    {
        dwRequestFlag = WINHTTP_FLAG_SECURE;
    }

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        szMethod.c_str(),
        stUrlStruct.szPath.c_str(),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        dwRequestFlag);

    if (hRequest == NULL)
    {
        return NULL;
    }

    for (auto &cp : lpHttp->mpRequestHeader)
    {
        CQWSTR szEntry;
        szEntry.append(cp.first);
        szEntry.append(L": ");
        szEntry.append(cp.second);

        WinHttpAddRequestHeaders(hRequest, szEntry.c_str(), (DWORD)(-1), WINHTTP_ADDREQ_FLAG_ADD);
    }
    return hRequest;
}

static BOOL ReadRequestBodyOnce(HINTERNET hRequest, CQHTTP *lpHttp, CONST BYTE *lpBytes, DWORD dwLength)
{
    DWORD dwWritten = 0;
    while (dwWritten < dwLength)
    {
        DWORD dwLeft = dwLength - dwWritten;
        DWORD dwThisWritten = 0;

        BOOL bOkay = WinHttpWriteData(hRequest, lpBytes + dwWritten, dwLeft, &dwThisWritten);
        if (!bOkay)
        {
            return FALSE;
        }

        dwWritten += dwThisWritten;

        //pause 50 milliseonds before writing the data next time.
        if (dwThisWritten < dwLeft)
        {
            Sleep(50);
        }
    }

    return TRUE;
}

static BOOL ReadRequestBody(HINTERNET hRequest, CQHTTP *lpHttp)
{
    if (lpHttp->fnRequestBodyReader != NULL)
    {
        CQVEC<BYTE> vcBytes(4 * 1024);
        
        while (TRUE)
        {
            int nLength = lpHttp->fnRequestBodyReader(vcBytes.data(), (int)vcBytes.size());
            if (nLength == -1)
            {
                //transfer finished.
                return TRUE;
            }

            BOOL bWriteOkay = ReadRequestBodyOnce(hRequest, lpHttp, vcBytes.data(), nLength);
            if (!bWriteOkay)
            {
                //transfer error.
                return FALSE;
            }
        }
    }
    else
    {
        CONST BYTE *lpBytes = lpHttp->vcRequestBodyData.data();
        DWORD dwLength = (DWORD)lpHttp->vcRequestBodyData.size();

        return ReadRequestBodyOnce(hRequest, lpHttp, lpBytes, dwLength);
    }
}

static BOOL WriteResponseCode(HINTERNET hRequest, CQHTTP *lpHttp)
{
    DWORD dwCode = 0;
    DWORD dwSize = sizeof(DWORD);

    BOOL bOkay = WinHttpQueryHeaders(
        hRequest,
        WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX,
        &dwCode,
        &dwSize,
        WINHTTP_NO_HEADER_INDEX);

    if (bOkay)
    {
        lpHttp->nResponseCode = dwCode;
    }
    return bOkay;
}

static VOID GetResponseHeaderFromRaw(CONST CQVEC<WCHAR> &vcData, CQMAP<CQWSTR, CQWSTR> *lpHeader)
{
    CONST WCHAR *lpRead = vcData.data();
    CONST WCHAR *lpEnd = vcData.data() + vcData.size();

    //skip first line:
    while (lpRead < lpEnd)
    {
        if (lpRead[0] == L'\r' && lpRead + 1 < lpEnd && lpRead[1] == L'\n')
        {
            lpRead += 2;
            break;
        }
        else
        {
            lpRead += 1;
        }
    }

    //every entries:
    BOOL bReadField = TRUE;
    CQWSTR szField;
    CQWSTR szValue;
    while (lpRead < lpEnd)
    {
        if (lpRead[0] == L'\r' && lpRead + 1 < lpEnd && lpRead[1] == L'\n')
        {
            if (szField.empty() || szValue.empty())
            {
                //read finished.
                break;
            }
            else
            {
                //store current line:
                (*lpHeader)[szField] = szValue;

                //ready to read next line:
                bReadField = TRUE;
                szField.clear();
                szValue.clear();

                lpRead += 2;
            }
        }
        else if (lpRead[0] == L':' && lpRead + 1 < lpEnd && lpRead[1] == L' ')
        {
            bReadField = FALSE;
            lpRead += 2;
        }
        else
        {
            if (bReadField)
            {
                szField.append(1, *lpRead);
            }
            else
            {
                szValue.append(1, *lpRead);
            }
            lpRead += 1;
        }
    }
}

static BOOL WriteResponseHeader(HINTERNET hRequest, CQHTTP *lpHttp)
{
    //get header size:
    DWORD dwHeaderSize = 0;
    BOOL bOkay = WinHttpQueryHeaders(
        hRequest,
        WINHTTP_QUERY_RAW_HEADERS_CRLF,
        WINHTTP_HEADER_NAME_BY_INDEX,
        NULL,
        &dwHeaderSize,
        WINHTTP_NO_HEADER_INDEX);

    if (bOkay || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        return FALSE;
    }

    //get header:
    CQVEC<WCHAR> vcHeaderData(dwHeaderSize / sizeof(WCHAR));
    bOkay = WinHttpQueryHeaders(
        hRequest,
        WINHTTP_QUERY_RAW_HEADERS_CRLF,
        WINHTTP_HEADER_NAME_BY_INDEX,
        vcHeaderData.data(),
        &dwHeaderSize,
        WINHTTP_NO_HEADER_INDEX);

    if (bOkay)
    {
        GetResponseHeaderFromRaw(vcHeaderData, &lpHttp->mpResponseHeader);
    }
    return bOkay;
}

static BOOL WriteResponseBody(HINTERNET hRequest, CQHTTP *lpHttp)
{
    //get body size:
    DWORD dwBodySize = 0;
    BOOL bGotBodySize = WinHttpQueryDataAvailable(hRequest, &dwBodySize);
    if (!bGotBodySize)
    {
        return FALSE;
    }

    //get body:
    CQVEC<BYTE> vcBuffer(4 * 1024);
    BYTE *lpBuffer = vcBuffer.data();
    DWORD dwBufferSize = (DWORD)vcBuffer.size();

    DWORD dwReadSize = 0;
    while (dwReadSize < dwBodySize)
    {
        DWORD dwThisReadSize = 0;
        BOOL bReadOkay = WinHttpReadData(hRequest, lpBuffer, dwBufferSize, &dwThisReadSize);
        if (!bReadOkay)
        {
            return FALSE;
        }

        if (lpHttp->fnResponseBodyWriter != NULL)
        {
            BOOL bCarryOkay = lpHttp->fnResponseBodyWriter(lpBuffer, dwThisReadSize);
            if (bCarryOkay)
            {
                //stop transfer.
                return TRUE;
            }
        }
        else
        {
            auto &vcBytes = lpHttp->vcResponseBodyData;
            vcBytes.insert(vcBytes.end(), lpBuffer, lpBuffer + dwThisReadSize);
        }
        dwReadSize += dwThisReadSize;
    }
    return TRUE;
}

VOID CQHttpSyncResume(CQHTTP *lpHttp)
{
    if (lpHttp == NULL)
    {
        return;
    }

    //reset:
    lpHttp->szError.clear();
    lpHttp->nResponseCode = 0;
    lpHttp->mpResponseHeader.clear();
    lpHttp->vcResponseBodyData.clear();

    HINTERNET hSession = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    BOOL bError = TRUE;
    do
    {
        //request:
        URLSTRUCT stUrlStruct = UrlStruct(lpHttp->szUrlString, lpHttp->mpUrlQuery);

        hSession = OpenHttpSession(lpHttp);
        if (hSession == NULL)
        {
            break;
        }
        hConnect = OpenHttpConnect(hSession, lpHttp, stUrlStruct);
        if (hConnect == NULL)
        {
            break;
        }
        hRequest = OpenHttpRequest(hConnect, lpHttp, stUrlStruct);
        if (hRequest == NULL)
        {
            break;
        }

        BOOL bRequestOkay = WinHttpSendRequest(hRequest, NULL, 0, NULL, 0, 0, NULL);
        if (!bRequestOkay)
        {
            break;
        }
        if (_wcsicmp(lpHttp->szMethod.c_str(), L"post") == 0
         || _wcsicmp(lpHttp->szMethod.c_str(), L"get" ) == 0)
        {
            BOOL bRequestBodyOkay = ReadRequestBody(hRequest, lpHttp);
            if (!bRequestBodyOkay)
            {
                break;
            }
        }

        //response:
        BOOL bResponseOkay = WinHttpReceiveResponse(hRequest, NULL);
        if (!bResponseOkay)
        {
            break;
        }

        BOOL bResponseCodeOkay = WriteResponseCode(hRequest, lpHttp);
        if (!bResponseCodeOkay)
        {
            break;
        }
        BOOL bResponseHeaderOkay = WriteResponseHeader(hRequest, lpHttp);
        if (!bResponseHeaderOkay)
        {
            break;
        }
        BOOL bResponseBodyOkay = WriteResponseBody(hRequest, lpHttp);
        if (!bResponseBodyOkay)
        {
            break;
        }

        bError = FALSE;
    }
    while (0);

    if (hRequest) {WinHttpCloseHandle(hRequest);}
    if (hConnect) {WinHttpCloseHandle(hConnect);}
    if (hSession) {WinHttpCloseHandle(hSession);}

    if (bError)
    {
        lpHttp->szError = CQGetLastErrorW();
    }
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
