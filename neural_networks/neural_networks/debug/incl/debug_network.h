#pragma once

#include "network.h"


namespace Neural_networks
{
	namespace Debug
	{
		extern void debug_network(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Network& test_network);
		extern void debug_network(void);
	};
};