#pragma once

#include <string_view>
#include <vector>

std::vector<std::string_view> SplitText(std::string_view& str, const std::string_view& elem);
std::vector<std::string_view> SplitLine(std::string_view text);