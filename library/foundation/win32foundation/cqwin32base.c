#include "cqwin32base.h"

LPCWSTR CQWideStringFromMBS(LPCSTR pszMBS)
{
    if (cq_str_empty(pszMBS))
    {
        return NULL;
    }

    cq_auto_pool
    {
        int nMBS = (int)strlen(pszMBS);
        int nWS = MultiByteToWideChar(CP_ACP, 0, pszMBS, nMBS, NULL, 0);

        LPWSTR pszWS = cq_auto_array(sizeof(WCHAR), nWS + 1);
        MultiByteToWideChar(CP_ACP, 0, pszMBS, nMBS, pszWS, nWS);
        pszWS[nWS] = L'\0';

        return cq_store_wstr(pszWS);
    }

    return NULL;
}

LPCSTR CQMBStringFormWS(LPCWSTR pszWS)
{
    if (cq_wstr_empty(pszWS))
    {
        return NULL;
    }

    cq_auto_pool
    {
        int nWS = (int)wcslen(pszWS);
        int nMBS = WideCharToMultiByte(CP_ACP, 0, pszWS, nWS, NULL, 0, NULL, NULL);

        LPSTR pszMBS = cq_auto_array(sizeof(CHAR), nMBS + 1);
        WideCharToMultiByte(CP_ACP, 0, pszWS, nWS, pszMBS, nMBS, NULL, NULL);
        pszMBS[nMBS] = '\0';

        return cq_store_str(pszMBS);
    }

    return NULL;
}
