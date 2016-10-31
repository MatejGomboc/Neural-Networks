#include "stdafx.h"
#include <iostream>

#include "debug_network.h"
#include "simulation.h"

using namespace std;
using namespace neural_networks;

int main(int argc, char* argv[])
{
	while(true)
	{
		debug::debug_network();
		test_genetic_algorythm();
	}
	return 0;
}