#include <arpa/inet.h>
#include <unistd.h>

_CQCTOOL_BEGIN_VERSION_NS

in_addr cq_inet_addr(const char *str) {
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

in_addr cq_inet_addr(const std::string &str) {
    return cq_inet_addr(str.c_str());
}

in6_addr cq_inet6_addr(const std::string &str) {
    return cq_inet6_addr(str.c_str());
}

std::string cq_inet_str(in_addr addr) {
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
    int rawsock = socket(af, sock, ipproto);
    if (rawsock != -1) {
        return (cq_sock)(intptr_t)rawsock;
    } else {
        return nullptr;
    }
}

cq_sock cq_open_tcp_sock () { return open_sock(AF_INET , SOCK_STREAM, IPPROTO_TCP); }
cq_sock cq_open_tcp_sock6() { return open_sock(AF_INET6, SOCK_STREAM, IPPROTO_TCP); }
cq_sock cq_open_udp_sock () { return open_sock(AF_INET , SOCK_DGRAM , IPPROTO_UDP); }
cq_sock cq_open_udp_sock6() { return open_sock(AF_INET6, SOCK_DGRAM , IPPROTO_UDP); }

void cq_close_sock(cq_sock sock) {
    close(*(int *)sock);
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
    auto rawsock = *(int *)&sock;
    auto retcode = bind(rawsock, local.addr(), local.ulen());
    return retcode == 0;
}

bool cq_bind_sock(cq_sock sock, cq_sockaddr_in6 local) {
    auto rawsock = *(int *)&sock;
    auto retcode = bind(rawsock, local.addr(), local.ulen());
    return retcode == 0;
}

int cq_sock_sendto(cq_sock sock, cq_sockaddr_in remote, const void *dat, int datlen) {
    auto rawsock = *(int *)&sock;
    auto sendlen = (int)sendto(rawsock, dat, datlen, 0, remote.addr(), remote.ulen());
    return sendlen;
}

int cq_sock_sendto(cq_sock sock, cq_sockaddr_in6 remote, const void *dat, int datlen) {
    auto rawsock = *(int *)&sock;
    auto sendlen = (int)sendto(rawsock, dat, datlen, 0, remote.addr(), remote.ulen());
    return sendlen;
}

int cq_sock_recvfrom(cq_sock sock, cq_sockaddr_in *remote, void *buf, int buflen) {
    auto rawsock = *(int *)&sock;
    auto addrlen = (socklen_t)remote->ulen();
    auto retcode = (int)recvfrom(rawsock, buf, buflen, 0, remote->addr(), &addrlen);
    return retcode;
}

int cq_sock_recvfrom(cq_sock sock, cq_sockaddr_in6 *remote, void *buf, int buflen) {
    auto rawsock = *(int *)&sock;
    auto addrlen = (socklen_t)remote->ulen();
    auto retcode = (int)recvfrom(rawsock, buf, buflen, 0, remote->addr(), &addrlen);
    return retcode;
}

_CQCTOOL_END_VERSION_NS
