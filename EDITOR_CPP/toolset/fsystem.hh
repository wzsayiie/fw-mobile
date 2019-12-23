#pragma once

#include "_fsys.hh"

bool read_file(const string &path, vector<char> *out);

//write file, NOTE: if $dat is empty, the file will be cleared.
bool write_file(const string &path, const vector<char> &dat);

struct traverse_item {
    file_info file;
    int deep = 0;
};

typedef function<void (traverse_item item)> traverse_fn;

//traverse directory. if $path is not a directory, return false.
bool traverse(const string &path, traverse_fn fn);
