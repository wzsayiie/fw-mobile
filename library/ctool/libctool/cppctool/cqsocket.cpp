#include "cqsocket.hh"

_CQCTOOL_BEGIN_VERSION_NS

//sockaddr_in:

sockaddr_in_n::sockaddr_in_n() {
    reset(nullptr, 0);
}

sockaddr_in_n::sockaddr_in_n(const char *host, uint16_t port) {
    reset(host, port);
}

sockaddr_in_n::sockaddr_in_n(const std::string &host, uint16_t port) {
    reset(host, port);
}

void sockaddr_in_n::reset(const char *host, uint16_t port) {
    memset(&value, 0, sizeof(value));
    
    value.sin_family = AF_INET;
    value.sin_addr = inet_addr_n(host);
    value.sin_port = htons(port);
}

void sockaddr_in_n::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), 0);
}

std::string sockaddr_in_n::host() const {
    return inet_str_n(value.sin_addr);
}

uint16_t sockaddr_in_n::port() const {
    return value.sin_port;
}

size_t sockaddr_in_n::size() const {
    return sizeof(value);
}

sockaddr_in *sockaddr_in_n::addr_in() {
    return &value;
}

sockaddr *sockaddr_in_n::addr() {
    return (sockaddr *)&value;
}

//sockaddr_in6:

sockaddr_in6_n::sockaddr_in6_n() {
    reset(nullptr, 0);
}

sockaddr_in6_n::sockaddr_in6_n(const char *host, uint16_t port) {
    reset(host, port);
}

sockaddr_in6_n::sockaddr_in6_n(const std::string &host, uint16_t port) {
    reset(host, port);
}

void sockaddr_in6_n::reset(const char *host, uint16_t port) {
    memset(&value, 0, sizeof(value));
    
    value.sin6_family = AF_INET6;
    value.sin6_addr = inet6_addr_n(host);
    value.sin6_port = htons(port);
}

void sockaddr_in6_n::reset(const std::string &host, uint16_t port) {
    reset(host.c_str(), port);
}

std::string sockaddr_in6_n::host() const {
    return inet6_str_n(value.sin6_addr);
}

uint16_t sockaddr_in6_n::port() const {
    return value.sin6_port;
}

size_t sockaddr_in6_n::size() const {
    return sizeof(value);
}

sockaddr_in6 *sockaddr_in6_n::addr_in6() {
    return &value;
}

sockaddr *sockaddr_in6_n::addr() {
    return (sockaddr *)&value;
}

# if CQ_ON_WINDOWS
#   include "cqsocket_win.hpp"
# else
#   include "cqsocket_posix.hpp"
# endif

_CQCTOOL_END_VERSION_NS
