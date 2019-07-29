#pragma once

#include "cqwin32base.h"

typedef struct CQHTTP CQHTTP, *LPCQHTTP;

CQ_C_LINK LPCQHTTP CQHttpOpen(VOID);

CQ_C_LINK VOID CQHttpSetMethodW(LPCQHTTP lpHttp, LPCWSTR pszMethod);
CQ_C_LINK VOID CQHttpSetMethodA(LPCQHTTP lpHttp, LPCSTR  pszMethod);

CQ_C_LINK VOID CQHttpSetUrlW(LPCQHTTP lpHttp, LPCWSTR pszUrl);
CQ_C_LINK VOID CQHttpSetUrlA(LPCQHTTP lpHttp, LPCSTR  pszUrl);

//CQHTTP will perform the percent escape on its own.
CQ_C_LINK VOID CQHttpSetUrlQueryW(LPCQHTTP lpHttp, LPCWSTR pszField, LPCWSTR pszValue);
CQ_C_LINK VOID CQHttpSetUrlQueryA(LPCQHTTP lpHttp, LPCSTR  pszField, LPCSTR  pszValue);

CQ_C_LINK VOID CQHttpSetRequestHeaderW(LPCQHTTP lpHttp, LPCWSTR pszField, LPCWSTR pszValue);
CQ_C_LINK VOID CQHttpSetRequestHeaderA(LPCQHTTP lpHttp, LPCSTR  pszField, LPCSTR  pszValue);

//write request body. bEnd specifies write data finished or not.
//NOTE: this function could be call both before and after CQHttpConnect().
CQ_C_LINK VOID CQHtppSetRequestBody(LPCQHTTP lpHttp, LPBYTE lpBytes, DWORD dwSize, BOOL bEnd);

//if connect failed, return FASLE.
//NOTE: even fails, also need call CQHttpClose() to clean.
CQ_C_LINK BOOL CQHttpConnect(LPCQHTTP lpHttp);

CQ_C_LINK DWORD CQHttpGetResponseCode(LPCQHTTP lpHttp);

//return number of response header field pairs.
//NOTE: lpField and lpValue need to free().
CQ_C_LINK DWORD CQHttpGetResponseHeaderW(LPCQHTTP lpHttp, LPWSTR *lpField, LPWSTR *lpValue, DWORD dwIndex);
CQ_C_LINK DWORD CQHttpGetResponseHeaderA(LPCQHTTP lpHttp, LPSTR  *lpField, LPSTR  *lpValue, DWORD dwIndex);

//bCompleted specifies transfer finished or not.
//NOTE: return value need to free().
CQ_C_LINK LPBYTE CQHttpGetResponseBody(LPCQHTTP lpHttp, DWORD *lpSize, BOOL *bCompleted);

CQ_C_LINK VOID CQHttpClose(LPCQHTTP lpHttp);

# ifdef UNICODE
#   define CQHttpSetMethod         CQHttpSetMethodW
#   define CQHttpSetUrl            CQHttpSetUrlW
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryW
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderW
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderW
# else
#   define CQHttpSetMethod         CQHttpSetMethodA
#   define CQHttpSetUrl            CQHttpSetUrlA
#   define CQHttpSetUrlQuery       CQHttpSetUrlQueryA
#   define CQHttpSetRequestHeader  CQHttpSetRequestHeaderA
#   define CQHttpGetResponseHeader CQHttpGetResponseHeaderA
# endif
