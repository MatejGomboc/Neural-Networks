#pragma once

#include "member.h"
#include "neuron.h"
#include <vector>


namespace neural_networks
{
	typedef struct
	{
		// (0.0 - 1.0)

		double mut_probability_neuron_weight; // probability that one neuron's weight changes
		double mut_probability_output_weight; // probability that one output node's weight changes

		/*activation function*/
		double mut_probability_activ_treshold; // probability that neuron's activation function's treshold changes
		double mut_probability_activ_steepness; // probability that neuron's activation function's steepness changes
		double mut_probability_activ_simetricity; // probability that neuron's activation function's simetricity changes
		/*end activation function*/
	} t_mut_params;

	class population
	{
	public:
		t_mut_params mutation_params; // mutation parameters
		std::vector<member> members; // array of population members
	public:
		population(std::vector<member>::size_type N_members, std::vector<double>::size_type N_input_variables, std::vector<neuron>::size_type N_neurons, std::vector<double>::size_type N_output_variables, t_mut_params Mutation_params);
		~population(void);
		void calculate_outputs(void); // calculate output values of members
		void mutate(void); // mutate members of population
		void mate(void); // mate members of population, create new population
		std::vector<member>::size_type roulette_wheel(void); // roulette wheel selection algorithm
		std::vector<member>::size_type roulette_wheel(std::vector<member>::size_type dropped_memb_indx); // roulette wheel selection algorithm
		//std::vector<member>::size_type roulette_wheel(std::vector<std::vector<member>::size_type> dropped_memb_indx); // roulette wheel selection algorithm
	private:
		//bool is_in_array(std::vector<member>::size_type indx, std::vector<std::vector<member>::size_type> indx_array); // check if indx is in indx_array
	};
};