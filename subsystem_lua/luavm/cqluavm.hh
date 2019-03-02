#pragma once

#include <string>

void CQLuaVMOpen(const std::string &path);
void CQLuaVMClose();

void CQLuaVMDoString(const std::string &string);
