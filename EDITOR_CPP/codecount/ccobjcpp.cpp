#include "ccobjcpp.hh"

static bool ReadLineComment(const char **ptr, const char *end) {
    if (starts_with("//", *ptr, end)) {
        *ptr += 2;
    } else {
        return false;
    }
    
    while (*ptr < end) {
        if (**ptr == '\n') {
            *ptr += 1;
            break;
        } else {
            *ptr += 1;
        }
    }
    return true;
}

//parameter nCount is count of '\n'
static bool ReadParagraphComment(const char **ptr, const char *end, int *nCount) {
    if (starts_with("/*", *ptr, end)) {
        *ptr += 2;
    } else {
        return false;
    }
    
    while (*ptr < end) {
        if (starts_with("*/", *ptr, end)) {
            *ptr += 2;
            break;
        } else if (**ptr == '\n') {
            *ptr += 1;
            *nCount += 1;
        } else {
            *ptr += 1;
        }
    }
    return true;
}

static bool ReadLineString(const char **ptr, const char *end) {
    if /**/ (starts_with("\""  , *ptr, end)) { *ptr += 1; }
    else if (starts_with("L\"" , *ptr, end)) { *ptr += 2; }
    else if (starts_with("u8\"", *ptr, end)) { *ptr += 3; }
    else if (starts_with("u\"" , *ptr, end)) { *ptr += 2; }
    else if (starts_with("U\"" , *ptr, end)) { *ptr += 2; }
    else {
        return false;
    }
    
    while (*ptr < end) {
        if (starts_with("\\\"", *ptr, end)) {
            *ptr += 2;
        } else if (**ptr == '\"') {
            *ptr += 1;
            break;
        } else {
            *ptr += 1;
        }
    }
    return true;
}

//parameter nCount is count of '\n'
static bool ReadParagraphString(const char **ptr, const char *end, int *nCount) {
    if /**/ (starts_with("R\""  , *ptr, end)) { *ptr += 2; }
    else if (starts_with("LR\"" , *ptr, end)) { *ptr += 3; }
    else if (starts_with("u8R\"", *ptr, end)) { *ptr += 4; }
    else if (starts_with("uR\"" , *ptr, end)) { *ptr += 3; }
    else if (starts_with("UR\"" , *ptr, end)) { *ptr += 3; }
    else {
        return false;
    }
    
    string delimiter;
    while (*ptr < end) {
        if (**ptr == '(') {
            *ptr += 1;
            break;
        } else {
            delimiter.append(1, **ptr);
            *ptr += 1;
        }
    }
    delimiter.insert(delimiter.begin(), ')');
    delimiter.insert(delimiter.end()  , '"');
    
    while (*ptr < end) {
        if (starts_with(delimiter.c_str(), *ptr, end)) {
            *ptr += delimiter.size();
            break;
        } else if (**ptr == '\n') {
            *nCount += 1;
            *ptr += 1;
        } else {
            *ptr += 1;
        }
    }
    
    return true;
}

static void AccumulateAndReset(CCStatisticsData *data, CCContentMask *contents) {
    
    bool hasCode    = (*contents & CCContentMaskCode   );
    bool hasComment = (*contents & CCContentMaskComment);
    
    if /**/ (hasCode && hasComment) { data->codeAndCmnt += 1; }
    else if (hasCode              ) { data->codeLine    += 1; }
    else if (hasComment           ) { data->commentLine += 1; }
    else /* !hasCode,!hasComment */ { data->emptyLine   += 1; }
    
    *contents = 0;
}

static void ScanSourceOnce
    (const char **ptr,
     const char *end,
     CCContentMask *contents,
     CCStatisticsData *data)
{
    int nCount = 0;
    
    if (ReadLineComment(ptr, end)) {
        
        *contents |= CCContentMaskComment;
        AccumulateAndReset(data, contents);
        
    } else if (ReadParagraphComment(ptr, end, &nCount)) {
        
        if (nCount > 0) {
            //first line
            *contents |= CCContentMaskComment;
            AccumulateAndReset(data, contents);
            //lines in middle
            data->commentLine += nCount - 1;
            //last line
            *contents |= CCContentMaskComment;
        } else {
            *contents |= CCContentMaskComment;
        }
        
    } else if (ReadLineString(ptr, end)) {
        
        *contents |= CCContentMaskCode;
        
    } else if (ReadParagraphString(ptr, end, &nCount)) {
        
        if (nCount > 0) {
            //first line
            *contents |= CCContentMaskCode;
            AccumulateAndReset(data, contents);
            //lines in middle
            data->codeLine += nCount - 1;
            //last line
            *contents |= CCContentMaskCode;
        } else {
            *contents |= CCContentMaskCode;
        }
        
    } else if (**ptr == '\n') {
        
        AccumulateAndReset(data, contents);
        *ptr += 1;
        
    } else if (**ptr != ' ' && **ptr != '\t') {
        
        *contents |= CCContentMaskCode;
        *ptr += 1;
        
    } else {
        
        *ptr += 1;
    }
}

static void ScanSource(const vector<char> &bytes, CCStatisticsData *data) {
    
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    CCContentMask contents = 0;
    
    while (ptr < end) {
        ScanSourceOnce(&ptr, end, &contents, data);
    }
    AccumulateAndReset(data, &contents);
}

void CCObjcpp::onGetSupportedFiles(vector<string> *out) {
    *out = {".h", ".hh", ".m", ".mm", ".cpp"};
}

void CCObjcpp::onGetSupportedOptions(CCStatisticsMask *out) {
    *out  = 0;
    *out |= CCStatisticsMaskCodeLine   ;
    *out |= CCStatisticsMaskCodeAndCmnt;
    *out |= CCStatisticsMaskCommentLine;
    *out |= CCStatisticsMaskEmptyLine  ;
}

void CCObjcpp::onHandleFile(const vector<char> &bytes, CCStatisticsData *result) {
    ScanSource(bytes, result);
}
