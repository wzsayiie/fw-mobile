#include "cqsocket.hh"

_CQCTOOL_BEGIN_VERSION_NS

//sockaddr_in:

cq_sockaddr_in::cq_sockaddr_in(size_t len) {
    memset(_dat, 0, sizeof(_dat));
    _len = (int)len;
}

sockaddr *cq_sockaddr_in::addr() {
    return (sockaddr *)_dat;
}

uint32_t cq_sockaddr_in::ulen() {
    return (uint32_t)_len;
}

int32_t cq_sockaddr_in::slen() {
    return (int32_t)_len;
}

//sockaddr_in4:

cq_sockaddr_in4::cq_sockaddr_in4()
    : cq_sockaddr_in(sizeof(sockaddr_in))
{
    reset(nullptr, 0);
}

cq_sockaddr_in4::cq_sockaddr_in4(const char *host, uint16_t port)
    : cq_sockaddr_in(sizeof(sockaddr_in))
{
    reset(host, port);
}

cq_sockaddr_in4::cq_sockaddr_in4(const std::string &host, uint16_t port)
     : cq_sockaddr_in(sizeof(sockaddr_in))
{
    reset(host, port);
}

void cq_sockaddr_in4::reset(const char *host, uint16_t port) {
    sockaddr_in *addr = addr_in4();
    
    addr->sin_family = AF_INET;
    addr->sin_addr = cq_inet_addr(host);
    addr->sin_port = htons(port);
}

void cq_sockaddr_in4::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), 0);
}

std::string cq_sockaddr_in4::host() {
    return cq_inet_str(addr_in4()->sin_addr);
}

uint16_t cq_sockaddr_in4::port() {
    return addr_in4()->sin_port;
}

sockaddr_in *cq_sockaddr_in4::addr_in4() {
    return (sockaddr_in *)_dat;
}

//sockaddr_in6:

cq_sockaddr_in6::cq_sockaddr_in6()
    : cq_sockaddr_in(sizeof(sockaddr_in6))
{
    reset(nullptr, 0);
}

cq_sockaddr_in6::cq_sockaddr_in6(const char *host, uint16_t port)
    : cq_sockaddr_in(sizeof(sockaddr_in6))
{
    reset(host, port);
}

cq_sockaddr_in6::cq_sockaddr_in6(const std::string &host, uint16_t port)
    : cq_sockaddr_in(sizeof(sockaddr_in6))
{
    reset(host, port);
}

void cq_sockaddr_in6::reset(const char *host, uint16_t port) {
    sockaddr_in6 *addr = addr_in6();
    
    addr->sin6_family = AF_INET6;
    addr->sin6_addr = cq_inet6_addr(host);
    addr->sin6_port = htons(port);
}

void cq_sockaddr_in6::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), port);
}

std::string cq_sockaddr_in6::host() {
    return cq_inet6_str(addr_in6()->sin6_addr);
}

uint16_t cq_sockaddr_in6::port() {
    return addr_in6()->sin6_port;
}

sockaddr_in6 *cq_sockaddr_in6::addr_in6() {
    return (sockaddr_in6 *)_dat;
}

_CQCTOOL_END_VERSION_NS

# if CQ_ON_WINDOWS
#   include "cqsocket_win.hpp"
# else
#   include "cqsocket_posix.hpp"
# endif
