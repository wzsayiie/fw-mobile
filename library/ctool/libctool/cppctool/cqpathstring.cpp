#include "cqpathstring.hh"

CQ_IF_ON_ANDROID(static const char *sSeparator = "/" );
CQ_IF_ON_IOS    (static const char *sSeparator = "/" );
CQ_IF_ON_WINDOWS(static const char *sSeparator = "\\");
CQ_IF_ON_OSX    (static const char *sSeparator = "/" );

static bool isSeparator(char ch) {
    
    //on windows, '/' and '\\' both are separators;
    
    CQ_IF_ON_ANDROID(return ch == '/');
    CQ_IF_ON_IOS    (return ch == '/');
    CQ_IF_ON_WINDOWS(return ch == '/' || ch == '\\');
    CQ_IF_ON_OSX    (return ch == '/');
}

static bool isNotSeparator(char ch) {
    return !isSeparator(ch);
}

static bool isDot(char ch) {
    return ch == '.';
}

static const char *AdvanceUntil(const char *begin, const char *end, bool (*fn)(char)) {
    for (; begin < end; ++begin) {
        if (fn(*begin)) {
            break;
        }
    }
    return begin;
}

static const char *TruncateUntil(const char *begin, const char *end, bool (*fn)(char)) {
    for (; end > begin; --end) {
        if (fn(end[-1])) {
            break;
        }
    }
    return end;
}

std::string cqPathString::append(const std::string &path, const std::string &item) {
    auto pBegin = path.c_str();
    auto pEnd = TruncateUntil(pBegin, pBegin + path.size(), isNotSeparator);
    
    auto iBegin = AdvanceUntil(item.c_str(), item.c_str() + item.size(), isNotSeparator);
    auto iEnd = item.c_str() + item.size();
    
    if (pBegin == pEnd) {
        //if root directory:
        if (!CQ_ON_WINDOWS && !path.empty() && isSeparator(*pBegin)) {
            return std::string(sSeparator).append(iBegin, iEnd);
        } else {
            return std::string(iBegin, iEnd);
        }
    } else {
        if (iBegin < iEnd) {
            return std::string(pBegin, pEnd).append(sSeparator).append(iBegin, iEnd);
        } else {
            return std::string(pBegin, pEnd).append(iBegin, iEnd);
        }
    }
}

std::string cqPathString::localeDirectory(const std::string &path) {
    auto begin = path.c_str();
    auto end = TruncateUntil(begin, begin + path.size(), isNotSeparator);
    
    auto dirEnd = TruncateUntil(begin, end, isSeparator);
    if (begin < dirEnd) {
        //if root directory:
        if (!CQ_ON_WINDOWS && begin + 1 == dirEnd) {
            return sSeparator;
        } else {
            return std::string(begin, dirEnd - 1);
        }
    } else {
        return "";
    }
}

std::string cqPathString::fileName(const std::string &path) {
    auto begin = path.c_str();
    auto end = TruncateUntil(begin, begin + path.size(), isNotSeparator);
    
    //if not find separator, $dirEnd will equal with $begin.
    auto dirEnd = TruncateUntil(begin, end, isSeparator);
    return std::string(dirEnd);
}

std::string cqPathString::fileNameWithoutExtention(const std::string &path) {
    auto begin = path.c_str();
    auto end = TruncateUntil(begin, begin + path.size(), isNotSeparator);
    
    //if not find separator, $dirEnd will equal with $begin.
    auto dirEnd = TruncateUntil(begin, end, isSeparator);
    
    auto nameWithoutExtEnd = TruncateUntil(dirEnd, end, isDot);
    if (dirEnd < nameWithoutExtEnd) {
        //'.' is not first and last charactor:
        if (dirEnd + 1 != nameWithoutExtEnd && nameWithoutExtEnd != end) {
            return std::string(dirEnd, nameWithoutExtEnd - 1);
        } else {
            return std::string(dirEnd, end);
        }
    } else {
        return std::string(dirEnd, end);
    }
}

std::string cqPathString::extensionName(const std::string &path) {
    auto begin = path.c_str();
    auto end = TruncateUntil(begin, begin + path.size(), isNotSeparator);
    
    //if not find separator, $dirEnd will equal with $begin.
    auto dirEnd = TruncateUntil(begin, end, isSeparator);
    
    auto nameWithoutExtEnd = TruncateUntil(dirEnd, end, isDot);
    if (dirEnd < nameWithoutExtEnd) {
        //'.' is not first and last charactor:
        if (dirEnd + 1 != nameWithoutExtEnd && nameWithoutExtEnd != end) {
            return std::string(nameWithoutExtEnd, end);
        } else {
            return "";
        }
    } else {
        return "";
    }
}
