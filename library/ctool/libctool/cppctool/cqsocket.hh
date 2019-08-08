#pragma once

#include "cqctoolbase.hh"

# if CQ_ON_WINDOWS
#   include <winsock2.h>
# else
#   include <netinet/in.h>
#   include <sys/socket.h>
# endif

_CQCTOOL_BEGIN_VERSION_NS

# if !CQ_ON_WINDOWS
#   define SOCKET         int
#   define INVALID_SOCKET INT_MAX
#   define SOCKET_ERROR   (-1)
# endif

struct sockaddr_in_n {
    
    sockaddr_in_n();
    sockaddr_in_n(const char *host, uint16_t port);
    sockaddr_in_n(const std::string &host, uint16_t port);
    
    void reset(const char *host, uint16_t port);
    void reset(const std::string &host, uint16_t port);
    
    std::string host() const;
    uint16_t port() const;
    size_t size() const;
    
    sockaddr_in *addr_in();
    sockaddr *addr();
    
    sockaddr_in value;
};

struct sockaddr_in6_n {
    
    sockaddr_in6_n();
    sockaddr_in6_n(const char *host, uint16_t port);
    sockaddr_in6_n(const std::string &host, uint16_t port);
    
    void reset(const char *host, uint16_t port);
    void reset(const std::string &host, uint16_t port);
    
    std::string host() const;
    uint16_t port() const;
    size_t size() const;
    
    sockaddr_in6 *addr_in6();
    sockaddr *addr();
    
    sockaddr_in6 value;
};

in_addr  inet_addr_n (const char *str);
in6_addr inet6_addr_n(const char *str);
in_addr  inet_addr_n (const std::string &str);
in6_addr inet6_addr_n(const std::string &str);

std::string inet_str_n (in_addr  addr);
std::string inet6_str_n(in6_addr addr);

SOCKET socket_n(int af, int sock, int ipproto);
void close_n(SOCKET s);

const char *    _last_socket_error_n();
#define errno_n _last_socket_error_n()

_CQCTOOL_END_VERSION_NS
