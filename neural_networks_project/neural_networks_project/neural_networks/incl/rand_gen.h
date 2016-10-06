#pragma once

namespace neural_networks
{
	const double min_double = -1000.0, max_double = 1000.0; // max and min random double value that can be generated
	const int min_int = -1000, max_int = 1000; // max and min random int value that can be generated

	class rand_gen
	{
	public:
		rand_gen(void);
		~rand_gen(void);
		static double clamp_value(double value); // restrict input double value between max and min random double value that can be generated
		static int clamp_value(int value); // restrict input int value between max and min random int value that can be generated
		double random_double(void); // return random double value between max and min double value that can be generated
		double random_double(double min_val, double max_val); // return random double value between given max and min double values
		int random_int(void); // return random int value between max and min int value that can be generated
		int random_int(int min_val, int max_val); // return random int value between given max and min int values
	};
};

