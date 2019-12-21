#pragma once

#include "_fsys.hh"

//read and write file:

bool readf (const string &path, vector<char> *out);
bool writef(const string &path, const vector<char> &dat);

//traverse directory:

typedef function<void (const fitem &it, int deep)> scanfn;
bool scan(const string &path, scanfn fn);
