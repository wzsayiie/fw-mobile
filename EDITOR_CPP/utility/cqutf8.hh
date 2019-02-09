#pragma once

#include "cqahead.hh"

static const char *const CQUTF8BOM = "\xEF\xBB\xBF";
static const size_t CQUTF8BOMSize = 3;

bool CQStartsWithUTF8BOM(const char *ptr, const char *end);

size_t CQGetUTF8Char(const char *ptr, const char *end, char *ascii);
