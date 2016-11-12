#include "debug_population.h"
#include "debug_member.h"
#include "constants.h"
#include "rand_gen.h"
#include "population.h"

#include <vector>
#include <set>


namespace neural_networks
{
	namespace debug
	{
		extern void debug_population(const unsigned long N_members, const unsigned long N_memb_input_variables, const unsigned long N_memb_neurons,
			const unsigned long N_memb_output_variables, const Mutation_params mutation_params, Population& test_population)
		{
			if (mutation_params.m_dProb_mut_neuron_simetricity != test_population.m_mutation_params.m_dProb_mut_neuron_simetricity)
				throw "Invalid probability that neuron's activation function's simetricity changes.";

			if (mutation_params.m_dProb_mut_neuron_steepness != test_population.m_mutation_params.m_dProb_mut_neuron_steepness)
				throw "Invalid probability that neuron's activation function's steepness changes";

			if (mutation_params.m_dProb_mut_neuron_treshold != test_population.m_mutation_params.m_dProb_mut_neuron_treshold)
				throw "Invalid probability that neuron's activation function's treshold changes";

			if (mutation_params.m_dProb_mut_neuron_weight != test_population.m_mutation_params.m_dProb_mut_neuron_weight)
				throw "Invalid probability that one neuron's weight changes";

			if (mutation_params.m_dProb_mut_output_weight != test_population.m_mutation_params.m_dProb_mut_output_weight)
				throw "Invalid probability that one output node's weight changes";

			if (N_members != test_population.m_members.size()) throw "Invalid number of members in this population.";

			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				 debug_member(N_memb_input_variables, N_memb_neurons, N_memb_output_variables, test_population.m_members[i]);
			}
		}


		extern void debug_population(void)
		{
			const unsigned long N_members = 7;

			const unsigned long N_memb_input_variables = 5;
			const unsigned long N_memb_neurons = 10;
			const unsigned long N_memb_output_variables = 3;

			const Mutation_params mutation_params(random_double(probabilityMinValue, probabilityMaxValue),
				random_double(probabilityMinValue, probabilityMaxValue),
				random_double(probabilityMinValue, probabilityMaxValue),
				random_double(probabilityMinValue, probabilityMaxValue),
				random_double(probabilityMinValue, probabilityMaxValue));

			Population test_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params);

			debug_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params, test_population);

			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				test_population.m_members[i].m_dFitness = random_double(fitnessMinValue, fitnessMaxValue);
			}

			debug_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params, test_population);

			test_population.calculate_outputs();

			debug_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params, test_population);

			test_population.mutate();

			debug_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params, test_population);

			test_population.mate();

			debug_population(N_members, N_memb_input_variables, N_memb_neurons, N_memb_output_variables, mutation_params, test_population);
		}
	};
};