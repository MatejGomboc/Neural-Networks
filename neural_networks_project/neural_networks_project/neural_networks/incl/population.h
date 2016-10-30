#pragma once

#include "constants.h"
#include "restricted.h"
#include "srestricted.h"
#include "member.h"
#include <vector>
#include <set>


namespace neural_networks
{
	struct Mutation_params
	{
		Mutation_params(const double prob_mut_neuron_weight = 0.0, const double prob_mut_output_weight = 0.0,
		const double prob_mut_neuron_treshold = 0.0, const double prob_mut_neuron_steepness = 0.0,
		const double prob_mut_neuron_simetricity = 0.0);

		restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_weight; // probability that one neuron's weight changes (0.0 - 1.0)
		restricted_range::srestricted<double, 0, 1> m_dProb_mut_output_weight; // probability that one output node's weight changes (0.0 - 1.0)

		/*activation function*/
		restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_treshold; // probability that neuron's activation function's treshold changes (0.0 - 1.0)
		restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_steepness; // probability that neuron's activation function's steepness changes (0.0 - 1.0)
		restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_simetricity; // probability that neuron's activation function's simetricity changes (0.0 - 1.0)
		/*end activation function*/
	};

	class Population
	{
	public:
		Mutation_params m_mutation_params; // mutation parameters
		std::vector<Member> m_members; // array of population members
	public:
		Population(const unsigned long N_members, const unsigned long N_memb_input_variables, const unsigned long N_memb_neurons,
			const unsigned long N_memb_output_variables, const Mutation_params mutation_params);
		~Population(void);
		void calculate_outputs(void); // calculate output values of members
		void mutate(void); // mutate members of population
		void mate(void); // mate members of population, create new population
	private:
		// mute one double value if selection process (with given probability) successful
		void mutate_value(const double probability, restricted_range::restricted<double>& value_to_randomize);
		void mutate_value(const double probability, restricted_range::srestricted<double, 0, 1>& value_to_randomize);
		void mutate_value(const double probability, restricted_range::srestricted<double, -1000, 1000>& value_to_randomize);
		const unsigned long roulette_wheel(void); // roulette wheel selection algorithm
		const unsigned long roulette_wheel(const unsigned long dropped_memb_indx); // roulette wheel selection algorithm
		const unsigned long roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices); // roulette wheel selection algorithm
	};
}