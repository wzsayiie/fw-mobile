#pragma once

#include "std.hh"

//cross platform

#if defined(WIN32)
const char pathdiv = '\\';
#else
const char pathdiv = '/';
#endif

vector<string> splitpath(const string &path);
string basename(const string &path);
string dirname(const string &path);

bool readf(const string &path, vector<char> *out);
bool writef(const string &path, const vector<char> &content);

struct scanit {
    string name;
    bool isdir;
    int deep;
};
typedef function<void (const scanit &item)> scanfn;
void scan(const string &path, scanfn fn);

//platform related

string getcwd();
bool chdir(const string &dir);

bool fexists(const string &path, bool *isdir);

struct fitem {
    string name;
    bool isdir;
};
vector<fitem> subitems(const string &dir, bool *err);
