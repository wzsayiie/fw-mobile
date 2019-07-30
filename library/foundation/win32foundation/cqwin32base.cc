#include "cqwin32base.hh"

_CQWIN32FOUNDATION_BEGIN_NS

CQWSTR CQWStr::Make(CONST WCHAR *lpWStr)
{
    return lpWStr ? lpWStr : L"";
}

BOOL CQWStr::Empty(CONST WCHAR *lpWStr)
{
    return lpWStr == NULL || *lpWStr == L'\0';
}

CQWSTR CQWStr::FromStr(CONST CHAR *pszStr)
{
    if (pszStr != NULL)
    {
        int nStr = (int)strlen(pszStr);
        int nWStr = MultiByteToWideChar(CP_ACP, 0, pszStr, nStr, NULL, 0);

        CQVEC<WCHAR> szWStr((size_t)nWStr + 1);
        MultiByteToWideChar(CP_ACP, 0, pszStr, nStr, szWStr.data(), nWStr);
        szWStr[nWStr] = L'\0';

        return szWStr.data();
    }
    else
    {
        return L"";
    }
}

CQWSTR CQWStr::FromStr(CONST CQSTR &szStr)
{
    return FromStr(szStr.c_str());
}

CQWSTR CQWStr::FromU8S(const char *pszStr)
{
    const char16_t *u16s = cq_u16sfrom8s(pszStr);
    return CQWStr::Make((CONST WCHAR *)u16s);
}

CQWSTR CQWStr::FromU8S(const std::string &szStr)
{
    return FromU8S(szStr.c_str());
}

CQSTR CQStr::Make(CONST CHAR *pszStr)
{
    return pszStr ? pszStr : "";
}

BOOL CQStr::Empty(CONST CHAR *pszStr)
{
    return pszStr == NULL || *pszStr == '\0';
}

CQSTR CQStr::From(CONST WCHAR *pszWStr)
{
    if (pszWStr != NULL)
    {
        int nWStr = (int)wcslen(pszWStr);
        int nStr = WideCharToMultiByte(CP_ACP, 0, pszWStr, nWStr, NULL, 0, NULL, NULL);

        CQVEC<CHAR> szStr((size_t)nStr + 1);
        WideCharToMultiByte(CP_ACP, 0, pszWStr, nWStr, szStr.data(), nStr, NULL, NULL);
        szStr[nStr] = '\0';
    
        return szStr.data();
    }
    else
    {
        return "";
    }
}

CQSTR CQStr::From(CONST CQWSTR &szWStr)
{
    return From(szWStr.c_str());
}

std::string CQU8Str::From(CONST WCHAR *pszWStr)
{
    const char *u8s = cq_u8sfrom16s((const char16_t *)pszWStr);
    return cqString::make(u8s);
}

std::string CQU8Str::From(CONST CQWSTR &szWStr)
{
    return From(szWStr.c_str());
}

_CQWIN32FOUNDATION_END_NS
