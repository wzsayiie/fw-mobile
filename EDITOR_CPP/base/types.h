#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>

using std::function;
using std::string;
using std::vector;
using std::map;
using std::set;

//note: if string == prefix, return false
bool has_prefix(const std::string &string, const std::string &prefix);

//note: if string == suffix, return false
bool has_suffix(const std::string &string, const std::string &suffix);
