#pragma once

#include <string>

void CQLuaVMOpen(const std::string &path);
void CQLuaVMClose();

void CQLuaVMDoFile(const std::string &fileName);
void CQLuaVMDoString(const std::string &string);
