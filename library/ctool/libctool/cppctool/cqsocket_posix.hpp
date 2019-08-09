#include <arpa/inet.h>
#include <unistd.h>

_CQCTOOL_BEGIN_VERSION_NS

in_addr cq_inet4_addr(const char *str) {
    in_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        inet_pton(AF_INET, str, &addr);
    }
    return addr;
}

in6_addr cq_inet6_addr(const char *str) {
    in6_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        inet_pton(AF_INET6, str, &addr);
    }
    return addr;
}

in_addr cq_inet4_addr(const std::string &str) {
    return cq_inet4_addr(str.c_str());
}

in6_addr cq_inet6_addr(const std::string &str) {
    return cq_inet6_addr(str.c_str());
}

std::string cq_inet4_str(in_addr addr) {
    char str[INET_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET, &addr, str, sizeof(str));
    return str;
}

std::string cq_inet6_str(in6_addr addr) {
    char str[INET6_ADDRSTRLEN] = {0};
    inet_ntop(AF_INET6, &addr, str, sizeof(str));
    return str;
}

static cq_sock open_sock(int af, int sock, int ipproto) {
    int raw = socket(af, sock, ipproto);
    if (raw != -1) {
        return (cq_sock)(intptr_t)raw;
    } else {
        return nullptr;
    }
}

cq_sock cq_open_tcp_sock4() { return open_sock(AF_INET , SOCK_STREAM, IPPROTO_TCP); }
cq_sock cq_open_tcp_sock6() { return open_sock(AF_INET6, SOCK_STREAM, IPPROTO_TCP); }
cq_sock cq_open_udp_sock4() { return open_sock(AF_INET , SOCK_DGRAM , IPPROTO_UDP); }
cq_sock cq_open_udp_sock6() { return open_sock(AF_INET6, SOCK_DGRAM , IPPROTO_UDP); }

void cq_close_sock(cq_sock sock) {
    close(*(int *)&sock);
}

const char *cq_sock_error() {
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

bool cq_bind_sock(cq_sock sock, cq_sockaddr_in local) {
    int raw = *(int *)&sock;
    int code = bind(raw, local.addr(), local.ulen());
    return code == 0;
}

int cq_sock_sendto(cq_sock sock, cq_sockaddr_in remote, const void *dat, int datlen) {
    int raw = *(int *)&sock;
    return (int)sendto(raw, dat, datlen, 0, remote.addr(), remote.ulen());
}

int cq_sock_recvfrom(cq_sock sock, cq_sockaddr_in *remote, void *buf, int buflen) {
    if (remote != nullptr) {
        int raw = *(int *)&sock;
        socklen_t addrlen = remote->ulen();
        return (int)recvfrom(raw, buf, buflen, 0, remote->addr(), &addrlen);
    } else {
        return 0;
    }
}

_CQCTOOL_END_VERSION_NS
