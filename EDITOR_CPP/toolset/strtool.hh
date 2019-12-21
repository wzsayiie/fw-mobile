#pragma once

#include "stdlibs.hh"

//string prefix and suffix:

bool startwith(const string &prefix, const char *ptr, const char *end);
bool endwith  (const string &suffix, const char *ptr, const char *end);
bool startwith(const string &prefix, const string &str);
bool endwith  (const string &suffix, const string &str);

//path string:

#ifdef _WIN32
    const char *const pathdiv = "\\";
#else
    const char *const pathdiv = "/";
#endif

vector<string> splitpath(const string &path);

string basename(const string &path);
string dirname (const string &path);

string joinpath(const string &dir, const string &subitem);

//code source extension:

bool codext(const string &name);
