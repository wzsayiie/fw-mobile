//

in_addr inet_addr_n(const char *str) {
    in_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        InetPtonA(AF_INET, str, &addr);
    }
    return addr;
}

in6_addr inet6_addr_n(const char *str) {
    in6_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        InetPtonA(AF_INET6, str, &addr);
    }
    return addr;
}

in_addr inet_addr_n(const std::string &str) {
    return inet_addr_n(str.c_str());
}

in6_addr inet6_addr_n(const std::string &str) {
    return inet6_addr_n(str.c_str());
}

std::string inet_str_n(in_addr addr) {
    char str[INET_ADDRSTRLEN];
    InetNtopA(AF_INET, &addr, str, sizeof(str));
    return str;
}

std::string inet6_str_n(in6_addr addr) {
    char str[INET6_ADDRSTRLEN];
    InetNtopA(AF_INET6, &addr, str, sizeof(str));
    return str;
}

SOCKET socket_n(int af, int sock, int ipproto) {
    static bool initialized = false;
    if (!initialized) {
        WSAData data;
        WSAStartup(MAKEWORD(2, 2), &data);
        initialized = true;
    }

    return socket(af, sock, ipproto);
}

void close_n(SOCKET s) {
    closesocket(s);
}

const char *_last_socket_error_n() {
    std::string ret;
    
    int nCode = WSAGetLastError();
    if (nCode != 0) {

        ret.append("WSAGetLastError:");
        ret.append(std::to_string(nCode));
        
        //NOTE: in english to avoid wide characters.
        DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT);
        LPSTR pszMessage = NULL;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            nCode,
            dwLanguageId,
            (LPSTR)&pszMessage,
            0,
            NULL);

        if (!cq_str_empty(pszMessage)) {
            ret.append(", ");
            ret.append(pszMessage);
            LocalFree(pszMessage);
        }
    }
    
    return cq_store_str(ret.c_str());
}
