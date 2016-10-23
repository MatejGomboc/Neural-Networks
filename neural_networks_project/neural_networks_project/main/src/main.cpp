#include "stdafx.h"
#include <iostream>

#include "debug.h"
#include "restricted.h"


int main(int argc, char* argv[])
{
	neural_networks::debug::debug_rand_gen_double("rand_test_output_histogram_double.csv");
	neural_networks::debug::debug_rand_gen_int("rand_test_output_histogram_int.csv");
	neural_networks::debug::debug_network();

	//while(true);

	return 0;
}