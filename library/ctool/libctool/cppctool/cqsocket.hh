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
    
    //if set $host to nullptr or "", means INADDR_ANY.
    
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
    
    //if set $host to nullptr or "", means INADDR_ANY.
    
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

//if create successful, return the socket;
//else return nullptr.
_socket_t _tcp_socket (); //socket(AF_INET , SOCK_STREAM, IPPROTO_TCP)
_socket_t _tcp_socket6(); //socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP)
_socket_t _udp_socket (); //socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP)
_socket_t _udp_socket6(); //socket(AF_INET6, SOCK_DGRAM , IPPROTO_UDP)

void _close(_socket_t so);

//if successful return true, else return false.
bool _bind(_socket_t localso, _sockaddr localaddr);

//if successful return true, else return false.
bool _listen(_socket_t localso);

//if return nullptr, meams $localso is already invalid, developer should close it.
_socket_t _accept(_socket_t localso, _sockaddr *endaddr);

//if successful return true, else return false.
bool _connect(_socket_t localso, _sockaddr endaddr);

//number of bytes of sent data.
//if return -1, means $so is already invalid, developer should close it.
int _send(_socket_t so, const void *dat, int datlen);

//number of bytes of received data.
//if return -1, means $so is already invalid, developer should close it.
int _recv(_socket_t so, void *buf, int buflen);

//number of bytes of sent data.
//if return -1, means $localso is already invalid, developer should close it.
int _sendto(_socket_t localso, _sockaddr endaddr, const void *dat, int datlen);

//number of bytes of received data.
//if return -1, means $localso is already invalid, developer should close it.
int _recvfrom(_socket_t localso, _sockaddr *endaddr, void *buf, int buflen);

//the last error message, equivalent to errno or WSAGetLastError().
const char *_sockerr();

_CQCTOOL_END_VERSION_NS
