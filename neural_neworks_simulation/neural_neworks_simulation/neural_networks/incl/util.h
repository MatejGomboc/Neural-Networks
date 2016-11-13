#pragma once


namespace neural_networks
{
	extern double clamp(const double value); // restrict input double value between max and min random double value that can be generated
	extern int    clamp(const int    value); // restrict input int value between max and min random int value that can be generated
	extern double wrap (const double value, const double min = -1000.0, const double max = 1000.0); // wrap the value around the limits
	extern int    wrap (const int value, const int min = -1000, const int max = 1000); // wrap the value around the limits
};