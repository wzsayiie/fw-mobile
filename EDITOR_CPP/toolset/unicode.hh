#pragma once

#include "stdlibs.hh"

static const char *const UTF8_BOM = "\xEF\xBB\xBF";
static const int UTF8_BOM_SIZE = 3;

//return size of character; if not utf8 character, return 0.
int check_utf8(const char *ptr, const char *end);
