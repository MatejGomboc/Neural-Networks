#pragma once


namespace neural_networks
{
	extern double clamp_value(const double value); // restrict input double value between max and min random double value that can be generated
	extern int    clamp_value(const int    value); // restrict input int value between max and min random int value that can be generated
};