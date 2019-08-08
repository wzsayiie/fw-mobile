#include <arpa/inet.h>
#include <unistd.h>

in_addr inet_addr_n(const char *str) {
    in_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        inet_pton(AF_INET, str, &addr);
    }
    return addr;
}

in6_addr inet6_addr_n(const char *str) {
    in6_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        inet_pton(AF_INET6, str, &addr);
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
    char str[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &addr, str, sizeof(str));
    return str;
}

std::string inet6_str_n(in6_addr addr) {
    char str[INET6_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET6, &addr, str, sizeof(str));
    return str;
}

SOCKET socket_n(int af, int sock, int ipproto) {
    SOCKET s = socket(af, sock, ipproto);
    if (s == -1) {
        return INVALID_SOCKET;
    } else {
        return s;
    }
}

void close_n(SOCKET s) {
    close(s);
}

const char *_last_socket_error_n() {
    std::string ret;
    
    int code = errno;
    if (code != 0) {
        ret.append("errno:");
        ret.append(std::to_string(code));
        ret.append(", ");
        ret.append(strerror(code));
    }
    
    return cq_store_str(ret.c_str());
}
