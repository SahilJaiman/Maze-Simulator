#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

std::vector<std::string> split_string_by_newline(const std::string& str)
{
	auto result = std::vector<std::string>{};
	auto ss = std::stringstream{ str };

	for (std::string line; std::getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}
