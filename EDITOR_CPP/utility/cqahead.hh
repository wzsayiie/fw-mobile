#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace std;

//note: if str == prefix, return false
bool CQStringHasPrefix(const string &str, const string &prefix);

//note: if str == suffix, return false
bool CQStringHasSuffix(const string &str, const string &suffix);
