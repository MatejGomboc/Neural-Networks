#pragma once

#include "population.h"


namespace neural_networks
{
	namespace debug
	{
		extern void debug_population(const unsigned long N_members, const unsigned long N_memb_input_variables,
			const unsigned long N_memb_neurons, const unsigned long N_memb_output_variables,
			const Mutation_params mutation_params, Population& test_population);
		extern void debug_population(void);
	}
};