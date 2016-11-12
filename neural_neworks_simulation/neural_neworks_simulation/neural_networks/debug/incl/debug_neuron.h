#pragma once

#include "neuron.h"

namespace neural_networks
{
	namespace debug
	{
		extern void debug_neuron(const unsigned long N_weights, const Neuron &test_neuron);
		extern void debug_neuron(void);
	}
};