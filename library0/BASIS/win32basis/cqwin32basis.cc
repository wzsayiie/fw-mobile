#include "cqwin32basis.hh"

_CQBASIS_BEGIN_VERSION_NS

CQWSTR CQGetLastErrorW()
{
    DWORD dwCode = GetLastError();
    if (dwCode == 0)
    {
        return L"";
    }

    CQWSTR szMessage;
    szMessage.append(L"GetLastError:");
    szMessage.append(std::to_wstring(dwCode));
        
    //NOTE: in english to avoid multi-byte characters.
    DWORD dwLang = MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT);
    LPWSTR lpText = NULL;
    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dwCode,
        dwLang,
        (LPWSTR)&lpText,
        0,
        NULL);

    if (lpText != NULL)
    {
        szMessage.append(L", ");
        szMessage.append(lpText);
        LocalFree(lpText);
    }

    return szMessage;
}

CQSTR CQGetLastErrorA()
{
    CQWSTR szMessage = CQGetLastErrorW();
    return CQStr_From(szMessage);
}

CQWSTR CQWStr_Make(CONST WCHAR *lpWStr)
{
    return lpWStr ? lpWStr : L"";
}

BOOL CQWStr_Empty(CONST WCHAR *lpWStr)
{
    return lpWStr == NULL || *lpWStr == L'\0';
}

CQWSTR CQWStr_FromStr(CONST CHAR *pszStr)
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

CQWSTR CQWStr_FromStr(CONST CQSTR &szStr)
{
    return CQWStr_FromStr(szStr.c_str());
}

CQWSTR CQWStr_FromU8S(const char *pszStr)
{
    const char16_t *u16s = cq_u16s_from8s(pszStr);
    return CQWStr_Make((CONST WCHAR *)u16s);
}

CQWSTR CQWStr_FromU8S(const std::string &szStr)
{
    return CQWStr_FromU8S(szStr.c_str());
}

CQSTR CQStr_Make(CONST CHAR *pszStr)
{
    return pszStr ? pszStr : "";
}

BOOL CQStr_Empty(CONST CHAR *pszStr)
{
    return pszStr == NULL || *pszStr == '\0';
}

CQSTR CQStr_From(CONST WCHAR *pszWStr)
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

CQSTR CQStr_From(CONST CQWSTR &szWStr)
{
    return CQStr_From(szWStr.c_str());
}

std::string CQU8Str_From(CONST WCHAR *pszWStr)
{
    const char *u8s = cq_u8s_from16s((const char16_t *)pszWStr);
    return cqString::make(u8s);
}

std::string CQU8Str_From(CONST CQWSTR &szWStr)
{
    return CQU8Str_From(szWStr.c_str());
}

_CQBASIS_END_VERSION_NS
