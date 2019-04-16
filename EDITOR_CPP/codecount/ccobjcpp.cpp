#include "ccobjcpp.hh"

static bool ReadLineComment(const char **ptr, const char *end) {
    if (begins_with("//", *ptr, end)) {
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
    if (begins_with("/*", *ptr, end)) {
        *ptr += 2;
    } else {
        return false;
    }
    
    while (*ptr < end) {
        if (begins_with("*/", *ptr, end)) {
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
    if /**/ (begins_with("\""  , *ptr, end)) { *ptr += 1; }
    else if (begins_with("L\"" , *ptr, end)) { *ptr += 2; }
    else if (begins_with("u8\"", *ptr, end)) { *ptr += 3; }
    else if (begins_with("u\"" , *ptr, end)) { *ptr += 2; }
    else if (begins_with("U\"" , *ptr, end)) { *ptr += 2; }
    else if (begins_with("@\"" , *ptr, end)) { *ptr += 2; }
    else {
        return false;
    }
    
    while (*ptr < end) {
        if (**ptr == '\"') {
            *ptr += 1;
            break;
        } else if (**ptr == '\\') {
            *ptr += 2;
        } else {
            *ptr += 1;
        }
    }
    return true;
}

//parameter nCount is count of '\n'
static bool ReadParagraphString(const char **ptr, const char *end, int *nCount) {
    if /**/ (begins_with("R\""  , *ptr, end)) { *ptr += 2; }
    else if (begins_with("LR\"" , *ptr, end)) { *ptr += 3; }
    else if (begins_with("u8R\"", *ptr, end)) { *ptr += 4; }
    else if (begins_with("uR\"" , *ptr, end)) { *ptr += 3; }
    else if (begins_with("UR\"" , *ptr, end)) { *ptr += 3; }
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
        if (begins_with(delimiter.c_str(), *ptr, end)) {
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

static bool ReadChar(const char **ptr, const char *end) {
    if (**ptr == '\'') {
        *ptr += 1;
    } else {
        return false;
    }
    
    while (*ptr < end) {
        if (**ptr == '\'') {
            *ptr += 1;
            break;
        } else if (**ptr == '\\') {
            *ptr += 2;
        } else {
            *ptr += 1;
        }
    }
    return true;
}

static void AccumulateAndReset(ccStatisticsData *data, ccContentMask *contents) {
    
    bool hasCode    = (*contents & ccContentMaskCode   );
    bool hasComment = (*contents & ccContentMaskComment);
    
    if /**/ (hasCode && hasComment) { data->codeAndCmnt += 1; }
    else if (hasCode              ) { data->codeLine    += 1; }
    else if (hasComment           ) { data->commentLine += 1; }
    else /* !hasCode,!hasComment */ { data->emptyLine   += 1; }
    
    *contents = 0;
}

static void ScanSourceOnce
    (const char **ptr,
     const char *end,
     ccContentMask *contents,
     ccStatisticsData *data)
{
    int nCount = 0;
    
    if (ReadLineComment(ptr, end)) {
        
        *contents |= ccContentMaskComment;
        AccumulateAndReset(data, contents);
        
    } else if (ReadParagraphComment(ptr, end, &nCount)) {
        
        if (nCount > 0) {
            //first line
            *contents |= ccContentMaskComment;
            AccumulateAndReset(data, contents);
            //lines in middle
            data->commentLine += nCount - 1;
            //last line
            *contents |= ccContentMaskComment;
        } else {
            *contents |= ccContentMaskComment;
        }
        
    } else if (ReadLineString(ptr, end)) {
        
        *contents |= ccContentMaskCode;
        
    } else if (ReadParagraphString(ptr, end, &nCount)) {
        
        if (nCount > 0) {
            //first line
            *contents |= ccContentMaskCode;
            AccumulateAndReset(data, contents);
            //lines in middle
            data->codeLine += nCount - 1;
            //last line
            *contents |= ccContentMaskCode;
        } else {
            *contents |= ccContentMaskCode;
        }
        
    } else if (ReadChar(ptr, end)) {
        
        *contents |= ccContentMaskCode;
        
    } else if (**ptr == '\n') {
        
        AccumulateAndReset(data, contents);
        *ptr += 1;
        
    } else if (**ptr != ' ' && **ptr != '\t') {
        
        *contents |= ccContentMaskCode;
        *ptr += 1;
        
    } else {
        
        *ptr += 1;
    }
}

static void ScanSource(const vector<char> &bytes, ccStatisticsData *data) {
    
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    ccContentMask contents = 0;
    
    while (ptr < end) {
        ScanSourceOnce(&ptr, end, &contents, data);
    }
    AccumulateAndReset(data, &contents);
}

void ccObjcpp::onGetSupportedFiles(vector<string> *out) {
    *out = {".h", ".hh", ".m", ".mm", ".cpp"};
}

void ccObjcpp::onGetSupportedOptions(ccStatisticsMask *out) {
    *out  = 0;
    *out |= ccStatisticsMaskCodeLine   ;
    *out |= ccStatisticsMaskCodeAndCmnt;
    *out |= ccStatisticsMaskCommentLine;
    *out |= ccStatisticsMaskEmptyLine  ;
}

void ccObjcpp::onHandleFile(const vector<char> &bytes, ccStatisticsData *result) {
    ScanSource(bytes, result);
}
