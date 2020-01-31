#pragma once

#include "_fsys.hh"

bool read_file(const string &path, vector<char> *out);
bool write_file(const string &path, const vector<char> &dat);

using traverse_fn = function<void (const file_info &file, int deep)>;

//traverse directory. if $path is not a directory, return false.
bool traverse(const string &path, traverse_fn fn);
