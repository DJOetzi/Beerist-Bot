#pragma once
#include <string>

namespace Utility::String
{
	auto str_contains(std::string s1, std::string s2) -> bool
	{
		return (s1.find(s2) != std::string::npos);
	}
}
