#include "cqdata_base64.hh"

static const char b64char[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

#define char0(a)    b64char[(                    ((uint8_t)a >> 2)) & 0x3F]
#define char1(a, b) b64char[(((uint8_t)a << 4) | ((uint8_t)b >> 4)) & 0x3F]
#define char2(b, c) b64char[(((uint8_t)b << 2) | ((uint8_t)c >> 6)) & 0x3F]
#define char3(c)    b64char[(((uint8_t)c     )                    ) & 0x3F]

std::string cqBase64::from(const void *bytes, size_t size) {
    if (bytes == nullptr && size <= 0) {
        return std::string();
    }
    
    std::string base64;
    
    auto cur = (const uint8_t *)bytes;
    auto end = (const uint8_t *)bytes + size;
    for (; cur + 3 <= end; cur += 3) /* continuous 3 bytes */ {
        
        base64.append(1, char0(cur[0]        ));
        base64.append(1, char1(cur[0], cur[1]));
        base64.append(1, char2(cur[1], cur[2]));
        base64.append(1, char3(cur[2]        ));
    }
    if (cur + 2 == end) /* 2 bytes left */ {
        
        base64.append(1, char0(cur[0]        ));
        base64.append(1, char1(cur[0], cur[1]));
        base64.append(1, char2(cur[1], 0     ));
        base64.append(1, '=');
    }
    else if (cur + 1 == end) /* 1 byte left */ {
        
        base64.append(1, char0(cur[0]   ));
        base64.append(1, char1(cur[0], 0));
        base64.append(1, '=');
        base64.append(1, '=');
    }
    
    return base64;
}

static uint8_t b64index(char ch) {
    
    if /**/ ('A' <= ch && ch <= 'Z') {return ch - 'A';}
    else if ('a' <= ch && ch <= 'z') {return ch - 'a' + 26;}
    else if ('0' <= ch && ch <= '9') {return ch - '0' + 52;}
    else if (ch == '+') {return 62;}
    else if (ch == '/') {return 63;}
    
    return 0xff;
}

static uint8_t syn0(uint8_t a, uint8_t b) {return (a << 2) | (b >> 4);}
static uint8_t syn1(uint8_t b, uint8_t c) {return (b << 4) | (c >> 2);}
static uint8_t syn2(uint8_t c, uint8_t d) {return (c << 6) | (d     );}

static bool push(std::vector<uint8_t> *data, char x, char y, decltype(syn0) syn) {
    uint8_t xi = b64index(x);
    if (xi >= 64) {
        return false;
    }
    uint8_t yi = b64index(y);
    if (yi >= 64) {
        return false;
    }
    data->push_back(syn(xi, yi));
    return true;
}

#define push0(v, a, b) push(v, a, b, syn0)
#define push1(v, b, c) push(v, b, c, syn1)
#define push2(v, c, d) push(v, c, d, syn2)

std::vector<uint8_t> cqBase64::decode(const std::string &base64) {
    std::vector<uint8_t> empty;
    std::vector<uint8_t> bytes;
    
    if (base64.empty()) {
        return empty;
    }
    if (base64.size() % 4 != 0) {
        return empty;
    }
    
    const char *cur  = base64.c_str();
    const char *end  = base64.c_str() + base64.size();
    const char *trim = (end[-1] != '=' ? end : end - 4);
    
    for (; cur < trim; cur += 4) /* continuous 'xxxx' */ {
        
        if (!push0(&bytes, cur[0], cur[1])) {return empty;}
        if (!push1(&bytes, cur[1], cur[2])) {return empty;}
        if (!push2(&bytes, cur[2], cur[3])) {return empty;}
    }
    if (cur < end && cur[2] != '=') /* ends with 'xxx=' */ {
        
        if (!push0(&bytes, cur[0], cur[1])) {return empty;}
        if (!push1(&bytes, cur[1], cur[2])) {return empty;}
    }
    else if (cur < end) /* ends with 'xx== '*/ {
        
        if (!push0(&bytes, cur[0], cur[1])) {return empty;}
    }
    
    return bytes;
}
