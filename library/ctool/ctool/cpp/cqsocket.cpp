#include "cqsocket.hh"

_CQCTOOL_BEGIN_VERSION_NS

//sockaddr:

_sockaddr::_sockaddr(size_t len) {
    memset(_dat, 0, sizeof(_dat));
    _len = (int)len;
}

sockaddr *_sockaddr::raw() {
    return (sockaddr *)_dat;
}

int _sockaddr::len() {
    return _len;
}

//sockaddr_in:

_sockaddr_in::_sockaddr_in()
    : _sockaddr(sizeof(sockaddr_in))
{
    reset(nullptr, 0);
}

_sockaddr_in::_sockaddr_in(const char *host, uint16_t port)
    : _sockaddr(sizeof(sockaddr_in))
{
    reset(host, port);
}

_sockaddr_in::_sockaddr_in(const std::string &host, uint16_t port)
    : _sockaddr(sizeof(sockaddr_in))
{
    reset(host, port);
}

void _sockaddr_in::reset(const char *host, uint16_t port) {
    sockaddr_in *addr = raw();
    
    addr->sin_family = AF_INET;
    addr->sin_addr = _inet_addr(host);
    addr->sin_port = htons(port);
}

void _sockaddr_in::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), 0);
}

std::string _sockaddr_in::host() {
    return _inet_str(raw()->sin_addr);
}

uint16_t _sockaddr_in::port() {
    return ntohs(raw()->sin_port);
}

sockaddr_in *_sockaddr_in::raw() {
    return (sockaddr_in *)_dat;
}

//sockaddr_in6:

_sockaddr_in6::_sockaddr_in6()
    : _sockaddr(sizeof(sockaddr_in6))
{
    reset(nullptr, 0);
}

_sockaddr_in6::_sockaddr_in6(const char *host, uint16_t port)
    : _sockaddr(sizeof(sockaddr_in6))
{
    reset(host, port);
}

_sockaddr_in6::_sockaddr_in6(const std::string &host, uint16_t port)
    : _sockaddr(sizeof(sockaddr_in6))
{
    reset(host, port);
}

void _sockaddr_in6::reset(const char *host, uint16_t port) {
    sockaddr_in6 *addr = raw();
    
    addr->sin6_family = AF_INET6;
    addr->sin6_addr = _inet6_addr(host);
    addr->sin6_port = htons(port);
}

void _sockaddr_in6::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), port);
}

std::string _sockaddr_in6::host() {
    return _inet6_str(raw()->sin6_addr);
}

uint16_t _sockaddr_in6::port() {
    return ntohs(raw()->sin6_port);
}

sockaddr_in6 *_sockaddr_in6::raw() {
    return (sockaddr_in6 *)_dat;
}

_CQCTOOL_END_VERSION_NS

# if CQ_ON_WINDOWS
#   include "cqsocket_win32.hpp"
# else
#   include "cqsocket_posix.hpp"
# endif
