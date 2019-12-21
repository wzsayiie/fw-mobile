#pragma once

#include "stdlibs.hh"

string getcwd();
bool chdir(const string &dir);

bool fexist(const string &path, bool *isdir);

struct fitem {
    bool isdir = false;
    string name;
};

//get subitems of directory. NOTE: hidden items will be ignored.
vector<fitem> subitems(const string &dir, bool *err);
