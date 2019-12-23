#pragma once

#include "stdlibs.hh"

static const char *const utf8_bom = "\xEF\xBB\xBF";

//return size of character; if not utf8 character, return 0.
int utf8_get(const char *ptr, const char *end);
