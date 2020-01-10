#pragma once

#include "stdlibs.hh"

//string prefix and suffix:

bool start_with(const string &prefix, const char *ptr, const char *end);
bool end_with  (const string &suffix, const char *ptr, const char *end);
bool start_with(const string &prefix, const string &str);
bool end_with  (const string &suffix, const string &str);

//format string:

# ifdef __GNUC__
#   define _Printf_format_string_
#   ifndef __printflike
#   define __printflike(F, A) __attribute((format(printf, F, A)))
#   endif
# else
#   include <sal.h>
#   define __printflike(F, A)
# endif

void append_format(string *str, _Printf_format_string_ const char *format, ...) __printflike(2, 3);
void assign_format(string *str, _Printf_format_string_ const char *format, ...) __printflike(2, 3);

//path string:

#ifdef _WIN32
    static const char *const path_div = "\\";
#else
    static const char *const path_div = "/";
#endif

vector<string> split_path(const string &path);

string parent_dir_of(const string &path);
string file_name_of (const string &path);

string join_path(const string &dir, const string &item);

//code source extension:

bool is_src_file(const string &name);
