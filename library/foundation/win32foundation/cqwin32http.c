#include "cqwin32http.h"
#include <winhttp.h>

struct CQHTTP {

    LPWSTR  pszMethod;
    LPWSTR  pszUrl;
    LPWSTR *lpUrlQuery;
    DWORD   dwUrlQuerySize;
    LPWSTR *lpRequestHeader;
    DWORD   dwRequestHeaderSize;
    LPBYTE  lpRequestBody;
    DWORD   dwRequestBodySize;
    BOOL    bRequestBodyEnd;

    DWORD   dwResponseCode;
    LPWSTR *lpResponseHeader;
    DWORD   dwResponseHeaderSize;
    LPBYTE  lpResponseBody;
    DWORD   dwResponseBodySize;
    BOOL    bTransferCompleted;
};

LPCQHTTP CQHttpOpen(VOID) {
    LPCQHTTP lpHttp = malloc(sizeof(CQHTTP));
    memset(lpHttp, 0, sizeof(CQHTTP));
    return lpHttp;
}

VOID CQHttpSetMethodW(LPCQHTTP lpHttp, LPCWSTR pszMethod) {
    if (lpHttp == NULL || cq_wstr_empty(pszMethod)) {
        return;
    }

    free(lpHttp->pszMethod);
    lpHttp->pszMethod = cq_copy_wstr(pszMethod);
}

VOID CQHttpSetMethodA(LPCQHTTP lpHttp, LPCSTR pszMethod) {
    CQHttpSetMethodW(lpHttp, CQWideStringFromMBS(pszMethod));
}

VOID CQHttpSetUrlW(LPCQHTTP lpHttp, LPCWSTR pszUrl) {
    if (lpHttp == NULL || cq_wstr_empty(pszUrl)) {
        return;
    }

    free(lpHttp->pszUrl);
    lpHttp->pszUrl = cq_copy_wstr(pszUrl);
}

VOID CQHttpSetUrlA(LPCQHTTP lpHttp, LPCSTR pszUrl) {
    CQHttpSetUrlW(lpHttp, CQWideStringFromMBS(pszUrl));
}

VOID CQHttpSetUrlQueryW(LPCQHTTP lpHttp, LPCWSTR pszField, LPCWSTR pszValue) {
    if (lpHttp == NULL || cq_wstr_empty(pszField) || cq_wstr_empty(pszValue)) {
        return;
    }

    LPWSTR *lpArray = lpHttp->lpUrlQuery;
    DWORD   dwArray = lpHttp->dwUrlQuerySize;

    lpArray = realloc(lpArray, sizeof(WCHAR *) * (dwArray + 2));
    lpArray[dwArray + 0] = cq_copy_wstr(pszField);
    lpArray[dwArray + 1] = cq_copy_wstr(pszValue);
    dwArray += 2;

    lpHttp->lpUrlQuery = lpArray;
    lpHttp->dwUrlQuerySize = dwArray;
}

VOID CQHttpSetUrlQueryA(LPCQHTTP lpHttp, LPCSTR pszField, LPCSTR pszValue) {
    cq_auto_pool
    {
        LPWSTR pszFieldW = cq_auto_wstr(CQWideStringFromMBS(pszField));
        LPWSTR pszValueW = cq_auto_wstr(CQWideStringFromMBS(pszValue));
        CQHttpSetUrlQueryW(lpHttp, pszFieldW, pszValueW);
    }
}

VOID CQHttpSetRequestHeaderW(LPCQHTTP lpHttp, LPCWSTR pszField, LPCWSTR pszValue) {
    if (lpHttp == NULL || cq_wstr_empty(pszField) || cq_wstr_empty(pszValue)) {
        return;
    }

    LPWSTR *lpArray = lpHttp->lpRequestHeader;
    DWORD   dwArray = lpHttp->dwRequestHeaderSize;

    lpArray = realloc(lpArray, sizeof(WCHAR *) * (dwArray + 2));
    lpArray[dwArray + 0] = cq_copy_wstr(pszField);
    lpArray[dwArray + 1] = cq_copy_wstr(pszValue);
    dwArray += 2;

    lpHttp->lpRequestHeader = lpArray;
    lpHttp->dwRequestHeaderSize = dwArray;
}

VOID CQHttpSetRequestHeaderA(LPCQHTTP lpHttp, LPCSTR pszField, LPCSTR pszValue) {
    cq_auto_pool
    {
        LPWSTR pszFieldW = cq_auto_wstr(CQWideStringFromMBS(pszField));
        LPWSTR pszValueW = cq_auto_wstr(CQWideStringFromMBS(pszValue));
        CQHttpSetRequestHeaderW(lpHttp, pszFieldW, pszValueW);
    }
}

VOID CQHtppSetRequestBody(LPCQHTTP lpHttp, LPBYTE lpBytes, DWORD dwSize, BOOL bEnd) {
    if (lpHttp == NULL || lpBytes == NULL || dwSize == 0 || lpHttp->bRequestBodyEnd) {
        return;
    }

    LPBYTE lpBody = lpHttp->lpRequestBody;
    DWORD  dwBody = lpHttp->dwRequestBodySize;

    lpBody = realloc(lpBody, dwBody + dwSize);
    memcpy(lpBody + dwBody, lpBytes, dwSize);
    dwBody += dwSize;

    lpHttp->lpRequestBody = lpBody;
    lpHttp->dwRequestBodySize = dwBody;
}

static LPWSTR GetHostFromUrl(LPCWSTR url) {
    return NULL;
}

static LPWSTR CopyPathFromUrl(LPCWSTR url, LPWSTR *lpQuery, DWORD dwQuerySize) {
    return NULL;
}

BOOL CQHttpConnect(LPCQHTTP lpHttp) {
    return FALSE;
}

DWORD CQHttpGetResponseCode(LPCQHTTP lpHttp) {
    if (lpHttp != NULL) {
        return lpHttp->dwResponseCode;
    } else {
        return 0;
    }
}

DWORD CQHttpGetResponseHeaderW(LPCQHTTP lpHttp, LPWSTR *lpField, LPWSTR *lpValue, DWORD dwIndex) {
    if (lpHttp == NULL) {
        return 0;
    }

    DWORD dwCountOfPairs = lpHttp->dwResponseHeaderSize / 2;
    if (lpField != NULL && lpValue != NULL && dwIndex < dwCountOfPairs) {
        *lpField = cq_copy_wstr(lpHttp->lpResponseHeader[dwIndex * 2 + 0]);
        *lpValue = cq_copy_wstr(lpHttp->lpResponseHeader[dwIndex * 2 + 1]);
    }
    return dwCountOfPairs;
}

DWORD CQHttpGetResponseHeaderA(LPCQHTTP lpHttp, LPSTR *lpField, LPSTR *lpValue, DWORD dwIndex) {
    LPWSTR lpFieldW = NULL;
    LPWSTR lpValueW = NULL;
    DWORD dwCOuntOfPairs = CQHttpGetResponseHeaderW(lpHttp, &lpFieldW, &lpValueW, dwIndex);

    if (lpField != NULL) { *lpField = cq_copy_str(CQMBStringFormWS(lpFieldW)); }
    if (lpValue != NULL) { *lpValue = cq_copy_str(CQMBStringFormWS(lpValueW)); }

    free(lpFieldW);
    free(lpValueW);

    return dwCOuntOfPairs;
}

LPBYTE CQHttpGetResponseBody(LPCQHTTP lpHttp, DWORD *lpSize, BOOL *bCompleted) {
    if (lpHttp == NULL || lpSize == NULL || bCompleted == NULL) {
        return NULL;
    }

    LPBYTE lpBody = lpHttp->lpResponseBody;
    *lpSize = lpHttp->dwResponseBodySize;
    *bCompleted = lpHttp->bTransferCompleted;

    lpHttp->lpResponseBody = NULL;
    lpHttp->dwResponseBodySize = 0;

    return lpBody;
}

VOID CQHttpClose(LPCQHTTP lpHttp) {
    if (lpHttp == NULL) {
        return;
    }

    //request data:
    free(lpHttp->pszMethod);
    free(lpHttp->pszUrl);

    for (DWORD it = 0; it < lpHttp->dwUrlQuerySize; ++it) {
        free(lpHttp->lpUrlQuery[it]);
    }
    free(lpHttp->lpUrlQuery);

    for (DWORD it = 0; it < lpHttp->dwRequestHeaderSize; ++it) {
        free(lpHttp->lpRequestHeader[it]);
    }
    free(lpHttp->lpRequestHeader);

    free(lpHttp->lpRequestBody);

    //response data:
    for (DWORD it = 0; it < lpHttp->dwResponseHeaderSize; ++it) {
        free(lpHttp->lpResponseHeader[it]);
    }
    free(lpHttp->lpResponseHeader);

    free(lpHttp->lpResponseBody);
}
