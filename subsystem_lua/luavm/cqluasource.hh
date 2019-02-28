#pragma once

#include <functional>
#include <string>

void CQLuaSourceUpdate(const std::string &path, std::function<void ()> completion);
