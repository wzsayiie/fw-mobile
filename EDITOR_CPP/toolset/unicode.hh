#pragma once

#include "stdlibs.hh"

static const char utf8bom[] = {'\xEF', '\xBB', '\xBF'};

//return size of character; if not utf8 character, return 0.
int utf8get(const char *ptr, const char *end);
