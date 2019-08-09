#pragma once

#include "cqctoolbase.hh"

# if CQ_ON_WINDOWS
#   include <winsock2.h>
#   include <ws2tcpip.h>
# else
#   include <netinet/in.h>
# endif

_CQCTOOL_BEGIN_VERSION_NS

struct _sockaddr {
    
protected:
    
    _sockaddr(size_t len);
    
public:
    
    sockaddr *raw();
    int len();
    
protected:
    
    char _dat[sizeof(sockaddr_in6)];
    int  _len;
};

struct _sockaddr_in : _sockaddr {
    
    _sockaddr_in();
    _sockaddr_in(const char *host, uint16_t port);
    _sockaddr_in(const std::string &host, uint16_t port);
    
    void reset(const char *host, uint16_t port);
    void reset(const std::string &host, uint16_t port);
    
    std::string host();
    uint16_t port();
    
    sockaddr_in *raw();
};

struct _sockaddr_in6 : _sockaddr {
    
    _sockaddr_in6();
    _sockaddr_in6(const char *host, uint16_t port);
    _sockaddr_in6(const std::string &host, uint16_t port);
    
    void reset(const char *host, uint16_t port);
    void reset(const std::string &host, uint16_t port);
    
    std::string host();
    uint16_t port();
    
    sockaddr_in6 *raw();
};

in_addr  _inet_addr (const char *str);
in6_addr _inet6_addr(const char *str);
in_addr  _inet_addr (const std::string &str);
in6_addr _inet6_addr(const std::string &str);

std::string _inet_str (in_addr  addr);
std::string _inet6_str(in6_addr addr);

typedef struct _CQ_SOCKET_T *_socket_t;

_socket_t _tcp_socket ();
_socket_t _tcp_socket6();
_socket_t _udp_socket ();
_socket_t _udp_socket6();

void _close(_socket_t so);

bool _bind(_socket_t localso, _sockaddr localaddr);

int _sendto(_socket_t localso, _sockaddr endaddr, const void *dat, int datlen);
int _recvfrom(_socket_t localso, _sockaddr *endaddr, void *buf, int buflen);

bool _listen(_socket_t localso);
_socket_t _accept(_socket_t localso, _sockaddr *endaddr);
bool _connect(_socket_t localso, _sockaddr endaddr);

int _send(_socket_t endso, const void *dat, int datlen);
int _recv(_socket_t endso, void *buf, int buflen);

const char *_error(_socket_t);

_CQCTOOL_END_VERSION_NS
