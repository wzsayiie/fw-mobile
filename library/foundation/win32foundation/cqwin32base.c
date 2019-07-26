#include "cqwin32base.h"

LPWSTR CQWideStringCopyFromMBS(LPCSTR pszMBS) {
    if (CQ_STR_EMPTY_W(pszMBS)) {
        return NULL;
    }

    int nMBS = (int)strlen(pszMBS);
    int nWS = MultiByteToWideChar(CP_ACP, 0, pszMBS, nMBS, NULL, 0);

    LPWSTR pszWS = malloc(((size_t)nWS + 1) * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pszMBS, nMBS, pszWS, nWS);
    pszWS[nWS] = L'\0';

    return pszWS;
}

LPSTR CQMultiByteStringCopyFromWS(LPCWSTR pszWS) {
    if (CQ_STR_EMPTY_W(pszWS)) {
        return NULL;
    }

    int nWS = (int)wcslen(pszWS);
    int nMBS = WideCharToMultiByte(CP_ACP, 0, pszWS, nWS, NULL, 0, NULL, NULL);

    LPSTR pszMBS = malloc(((size_t)nMBS + 1) * sizeof(CHAR));
    WideCharToMultiByte(CP_ACP, 0, pszWS, nWS, pszMBS, nMBS, NULL, NULL);
    pszMBS[nMBS] = '\0';

    return pszMBS;
}
