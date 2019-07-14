#pragma once

#include "std.hh"

static const char utf8bom[] = {'\xEF', '\xBB', '\xBF'};

//return size of character; if not utf8 character, return 0.
size_t utf8get(const char *ptr, const char *end);
