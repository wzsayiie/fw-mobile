#include "cqsocket.hh"

_CQCTOOL_BEGIN_VERSION_NS

//sockaddr_in:

cq_sockaddr_in::cq_sockaddr_in() {
    reset(nullptr, 0);
}

cq_sockaddr_in::cq_sockaddr_in(const char *host, uint16_t port) {
    reset(host, port);
}

cq_sockaddr_in::cq_sockaddr_in(const std::string &host, uint16_t port) {
    reset(host, port);
}

void cq_sockaddr_in::reset(const char *host, uint16_t port) {
    memset(&value, 0, sizeof(value));
    
    value.sin_family = AF_INET;
    value.sin_addr = cq_inet_addr(host);
    value.sin_port = htons(port);
}

void cq_sockaddr_in::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), 0);
}

std::string cq_sockaddr_in::host() const {
    return cq_inet_str(value.sin_addr);
}

uint16_t cq_sockaddr_in::port() const {
    return value.sin_port;
}

sockaddr_in *cq_sockaddr_in::addr_in() {
    return (sockaddr_in *)&value;
}

sockaddr *cq_sockaddr_in::addr() {
    return (sockaddr *)&value;
}

uint32_t cq_sockaddr_in::ulen() const {
    return (uint32_t)sizeof(value);
}

int32_t cq_sockaddr_in::slen() const {
    return (int32_t)sizeof(value);
}

//sockaddr_in6:

cq_sockaddr_in6::cq_sockaddr_in6() {
    reset(nullptr, 0);
}

cq_sockaddr_in6::cq_sockaddr_in6(const char *host, uint16_t port) {
    reset(host, port);
}

cq_sockaddr_in6::cq_sockaddr_in6(const std::string &host, uint16_t port) {
    reset(host, port);
}

void cq_sockaddr_in6::reset(const char *host, uint16_t port) {
    memset(&value, 0, sizeof(value));
    
    value.sin6_family = AF_INET6;
    value.sin6_addr = cq_inet6_addr(host);
    value.sin6_port = htons(port);
}

void cq_sockaddr_in6::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), port);
}

std::string cq_sockaddr_in6::host() const {
    return cq_inet6_str(value.sin6_addr);
}

uint16_t cq_sockaddr_in6::port() const {
    return value.sin6_port;
}

sockaddr_in6 *cq_sockaddr_in6::addr_in6() {
    return (sockaddr_in6 *)&value;
}

sockaddr *cq_sockaddr_in6::addr() {
    return (sockaddr *)&value;
}

uint32_t cq_sockaddr_in6::ulen() const {
    return (uint32_t)sizeof(value);
}

int32_t cq_sockaddr_in6::slen() const {
    return (int32_t)sizeof(value);
}

_CQCTOOL_END_VERSION_NS

# if CQ_ON_WINDOWS
#   include "cqsocket_win.hpp"
# else
#   include "cqsocket_posix.hpp"
# endif
