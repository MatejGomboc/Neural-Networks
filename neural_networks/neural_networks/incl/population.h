#pragma once

#include "restricted.h"
#include "srestricted.h"
#include "member.h"
#include "neural_network_exception.h"
#include <vector>
#include <set>
#include <memory>


namespace Neural_networks
{
	class Population_exception: public Neural_network_exception
	{
	public:
		explicit Population_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};


	struct Mutation_params
	{
		Mutation_params(const double prob_mut_neuron_weight = 0.0, const double prob_mut_output_weight = 0.0,
		const double prob_mut_neuron_treshold = 0.0, const double prob_mut_neuron_steepness = 0.0,
		const double prob_mut_neuron_simetricity = 0.0);

		Restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_weight; // probability that one neuron's weight changes (0.0 - 1.0)
		Restricted_range::srestricted<double, 0, 1> m_dProb_mut_output_weight; // probability that one output node's weight changes (0.0 - 1.0)

		/*activation function*/
		Restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_treshold; // probability that neuron's activation function's treshold changes (0.0 - 1.0)
		Restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_steepness; // probability that neuron's activation function's steepness changes (0.0 - 1.0)
		Restricted_range::srestricted<double, 0, 1> m_dProb_mut_neuron_simetricity; // probability that neuron's activation function's simetricity changes (0.0 - 1.0)
		/*end activation function*/
	};

	class Population
	{
	public:
		Mutation_params m_mutation_params; // mutation parameters
		std::vector<std::shared_ptr<Member>> m_pMembers; // array of population members
	public:
		
		Population(std::vector<std::shared_ptr<Member>>& members, const Mutation_params& mutation_params);
		~Population(void);

		void test(void) const; // check population for errors
		void calculate_outputs(void); // calculate output values of members
		void mutate(void); // mutate members of population
		void mate(void); // mate members of population, create new population

		// mute one double value if selection process (with given probability) successful
		static void mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
			Restricted_range::restricted<double>& value_to_randomize);
		static void mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
			Restricted_range::srestricted<double, 0, 1>& value_to_randomize);
		static void mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
			Restricted_range::srestricted<double, -1000, 1000>& value_to_randomize);

		unsigned long roulette_wheel(void) const; // roulette wheel selection algorithm
		unsigned long roulette_wheel(const unsigned long dropped_memb_indx) const; // roulette wheel selection algorithm
		unsigned long roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices) const; // roulette wheel selection algorithm
	};
};