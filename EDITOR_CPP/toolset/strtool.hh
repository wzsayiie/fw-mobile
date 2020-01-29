#pragma once

#include "stdlibs.hh"
#include "macro.hh"

//default byte buffer which developer can use to avoid "new" and "delete".
const int BYTE_BUF_SIZE = 1024 * 1024;
extern char BYTE_BUF[];

//test whether a string has a certain prefix(or suffix).
//NOTE: if the prefix(or suffix) is same as the string being tested, return true.
bool start_with(const string &word, const char *ptr, const char *end);
bool end_with  (const string &word, const char *ptr, const char *end);
bool start_with(const string &word, const string &str);
bool end_with  (const string &word, const string &str);

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

//TIP: use "*PATH_SEP" to get the separator its char type.
IF_ON_POSIX(static const char *const PATH_SEP = "/" );
IF_ON_WIN32(static const char *const PATH_SEP = "\\");

//EXAMPLE:
//  split_path("c:\\\\\\win\\") returns ["c:", "win"].
//  split_path("/usr/./../bin") returns ["/" , "usr", "bin"].
//
vector<string> split_path(const string &path);

string parent_dir_of(const string &path);
string file_name_of(const string &path);

//join parent directory and file name string, adding path separator if needed.
string join_path(const string &dir, const string &item);

static const char *SRC_FILE_EXT[] = {
    ".hh", ".hpp", ".cc"  , ".cxx", ".cpp",
    ".h" , ".m"  , ".mm"  ,
    ".cs", ".lua", ".java",
    nullptr
};

//determine a file is source of a programming language by file extension name.
//these extension names from "SRC_FILE_EXT".
bool is_src_file(const string &name);
