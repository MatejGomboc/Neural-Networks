#pragma once

#include <string>


namespace Utils
{
	// converts an integer to a std::string
	std::wstring itos(const int arg);

	// converts an float to a std::string
	std::wstring ftos(const float arg);

	// converts a std::string to std::wstring
	std::wstring string_to_wstring(const std::string arg);

	// clamps the first argument between the second two
	void clamp(double &arg, const double min, const double max);
}