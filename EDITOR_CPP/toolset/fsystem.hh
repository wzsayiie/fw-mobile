#pragma once

#include "stdlibs.hh"

//PLATFORM INDEPENDENT:

//path string operation:
#ifdef _WIN32
    const char pathdiv = '\\';
#else
    const char pathdiv = '/';
#endif

vector<string> splitpath(const string &path);

string basename(const string &path);
string dirname(const string &path);

string joinpath(const string &dir, const string &subitem);

//read and write file:
bool readf(const string &path, vector<char> *out);
bool writef(const string &path, const vector<char> &content);

//file item structure:
struct fitem {
    string name;
    bool isdir = false;
};

//traverse directory:
typedef function<void (const fitem &it, int deep)> scanfn;

//if $path exsits and $fn is not null, return true; else return false.
bool scan(const string &path, scanfn fn);

//PLATFORM RELATED:

//directory operation:
string getcwd();
bool chdir(const string &dir);

//file or directory exists:
bool fexists(const string &path, bool *isdir);

//get subitems of directory.
//NOTE: hidden files and directories will be ignored.
vector<fitem> subitems(const string &dir, bool *err);
