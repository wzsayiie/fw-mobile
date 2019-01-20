#include "utf8.h"
#include "filesystem.h"

static const char *const UTF8_BOM = "\xEF\xBB\xBF";

static size_t utf8_getch(const char *ptr, const char *end, char *ascii) {
    int size = 0;
    
    //check first byte
    if (ptr == nullptr) {
        return 0;
    }
    else if ((*ptr & 0b10'00'0000) == 0b00'00'0000) { size = 1; }
    else if ((*ptr & 0b11'10'0000) == 0b11'00'0000) { size = 2; }
    else if ((*ptr & 0b11'11'0000) == 0b11'10'0000) { size = 3; }
    else if ((*ptr & 0b11'11'1000) == 0b11'11'0000) { size = 4; }
    else {
        return 0;
    }
    if (ptr + size > end) {
        return 0;
    }
    
    //check followed bytes
    for (const char *it = ptr + 1; it < ptr + size; ++it) {
        if ((*it & 0b11'00'0000) != 0b10'00'0000) {
            return 0;
        }
    }
    
    //return
    if (ascii != nullptr) {
        if (size == 1) {
            *ascii = *ptr;
        } else {
            *ascii = 0;
        }
    }
    return size;
}

bool utf8_verify(
    const char *stream,
    const char *end,
    bool *only_ascii,
    bool *has_rn,
    bool *has_n,
    bool *has_r)
{
    return false;
}

bool utf8_fread(const string &path, utf8_finfo *info) {
    if (path.empty()) {
        return false;
    }
    if (info == nullptr) {
        return false;
    }
    
    vector<char> content;
    if (!fread(path, &content)) {
        return false;
    }
    
    size_t content_begin = 0;
    info->has_bom = false;
    if (content.size() >= 3 && strncmp(content.data(), UTF8_BOM, 3) == 0) {
        content_begin = 3;
        info->has_bom = true;
    }
    bool is_utf8 = utf8_verify(
        content.data() + content_begin,
        content.data() + content.size(),
        nullptr,
        &info->has_rn,
        &info->has_n,
        &info->has_r);
    
    return is_utf8;
}

bool utf8_fwrite(const string &path, const utf8_finfo &info) {
    return true;
}
