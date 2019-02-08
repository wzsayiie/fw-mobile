#pragma once

#include "cahead.h"

static const char *const CUTF8BOM = "\xEF\xBB\xBF";
static const size_t CUTF8BOMSize = 3;

bool CStartsWithUTF8BOM(const char *ptr, const char *end);

size_t CGetUTF8Char(const char *ptr, const char *end, char *ascii);
