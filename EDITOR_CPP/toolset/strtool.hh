#pragma once

#include "stdlibs.hh"

//string prefix and suffix:

bool startwith(const string &prefix, const char *ptr, const char *end);
bool endwith  (const string &suffix, const char *ptr, const char *end);
bool startwith(const string &prefix, const string &str);
bool endwith  (const string &suffix, const string &str);
