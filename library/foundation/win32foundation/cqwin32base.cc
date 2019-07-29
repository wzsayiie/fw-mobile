#include "cqwin32base.hh"

LPCWSTR cq_wsfrommbs(LPCSTR mbs)
{
    if (cq_str_empty(mbs))
    {
        return L"";
    }

    int mbscnt = (int)strlen(mbs);
    int wscnt = MultiByteToWideChar(CP_ACP, 0, mbs, mbscnt, NULL, 0);

    std::vector<wchar_t> ws(wscnt + 1);
    MultiByteToWideChar(CP_ACP, 0, mbs, mbscnt, ws.data(), wscnt);
    ws[wscnt] = L'\0';

    return cq_store_wstr(ws.data());
}

LPCSTR cq_mbsfromws(LPCWSTR ws)
{
    if (cq_wstr_empty(ws))
    {
        return "";
    }

    int wscnt = (int)wcslen(ws);
    int mbscnt = WideCharToMultiByte(CP_ACP, 0, ws, wscnt, NULL, 0, NULL, NULL);

    std::vector<char> mbs(mbscnt + 1);
    WideCharToMultiByte(CP_ACP, 0, ws, wscnt, mbs.data(), mbscnt, NULL, NULL);
    mbs[mbscnt] = '\0';

    return cq_store_str(mbs.data());
}
