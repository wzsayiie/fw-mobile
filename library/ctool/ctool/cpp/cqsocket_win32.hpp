//

_CQCTOOL_BEGIN_VERSION_NS

in_addr _inet_addr(const char *str) {
    in_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        InetPtonA(AF_INET, str, &addr);
    }
    return addr;
}

in6_addr _inet6_addr(const char *str) {
    in6_addr addr;
    memset(&addr, 0, sizeof(addr));
    
    if (str != nullptr) {
        InetPtonA(AF_INET6, str, &addr);
    }
    return addr;
}

in_addr _inet_addr(const std::string &str) {
    return _inet_addr(str.c_str());
}

in6_addr _inet6_addr(const std::string &str) {
    return _inet6_addr(str.c_str());
}

std::string _inet_str(in_addr addr) {
    char str[INET_ADDRSTRLEN] = {0};
    InetNtopA(AF_INET, &addr, str, sizeof(str));
    return str;
}

std::string _inet6_str(in6_addr addr) {
    char str[INET6_ADDRSTRLEN] = {0};
    InetNtopA(AF_INET6, &addr, str, sizeof(str));
    return str;
}

static _socket_t pkg(SOCKET so) {return (_socket_t)so;}
static SOCKET raw(_socket_t so) {return (SOCKET)so;}

static _socket_t _socket(int af, int sock, int ipproto) {
    static bool init = false;
    if (!init) {
        WSAData dat;
        WSAStartup(MAKEWORD(2, 2), &dat);
        init = true;
    }

    SOCKET so = socket(af, sock, ipproto);
    if (so != INVALID_SOCKET) {
        return pkg(so);
    } else {
        return nullptr;
    }
}

_socket_t _tcp_socket () { return _socket(AF_INET , SOCK_STREAM, IPPROTO_TCP); }
_socket_t _tcp_socket6() { return _socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP); }
_socket_t _udp_socket () { return _socket(AF_INET , SOCK_DGRAM , IPPROTO_UDP); }
_socket_t _udp_socket6() { return _socket(AF_INET6, SOCK_DGRAM , IPPROTO_UDP); }

void _close(_socket_t so) {
    closesocket(raw(so));
}

bool _bind(_socket_t localso, _sockaddr localaddr) {
    int code = bind(raw(localso), localaddr.raw(), localaddr.len());
    return code == 0;
}

bool _listen(_socket_t localso) {
    int code = listen(raw(localso), SOMAXCONN);
    return code == 0;
}

_socket_t _accept(_socket_t localso, _sockaddr *endaddr) {
    sockaddr *addr = endaddr ? endaddr->raw() : nullptr;
    int    addrlen = endaddr ? endaddr->len() : 0;

    SOCKET endso = accept(raw(localso), addr, &addrlen);
    return pkg(endso);
}

bool _connect(_socket_t localso, _sockaddr endaddr) {
    int code = connect(raw(localso), endaddr.raw(), endaddr.len());
    return code == 0;
}

int _send(_socket_t so, const void *dat, int datlen) {
    return send(raw(so), (const char *)dat, datlen, 0);
}

int _recv(_socket_t so, void *buf, int buflen) {
    return recv(raw(so), (char *)buf, buflen, 0);
}

int _sendto(_socket_t localso, _sockaddr endaddr, const void *dat, int datlen) {
    return sendto(raw(localso), (const char *)dat, datlen, 0, endaddr.raw(), endaddr.len());
}

int _recvfrom(_socket_t localso, _sockaddr *endaddr, void *buf, int buflen) {
    sockaddr *addr = endaddr ? endaddr->raw() : nullptr;
    int    addrlen = endaddr ? endaddr->len() : 0;

    return recvfrom(raw(localso), (char *)buf, buflen, 0, addr, &addrlen);
}

const char *_sockerr() {

    int code = WSAGetLastError();
    if (code == 0) {
        return cq_store_str(nullptr);
    }

    std::string msg;
    msg.append("WSAGetLastError:");
    msg.append(std::to_string(code));
        
    //NOTE: in english to avoid multi-byte characters.
    DWORD lang = MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT);
    LPSTR text = NULL;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        code,
        lang,
        (LPSTR)&text,
        0,
        NULL);

    if (text != nullptr) {
        msg.append(", ");
        msg.append(text);
        LocalFree(text);
    }

    return cq_store_str(msg.c_str());
}

_CQCTOOL_END_VERSION_NS
