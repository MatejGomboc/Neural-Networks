#pragma once

#include "member.h"
#include "constants.h"
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


	class Mutation_params
	{
	private:
		double m_dProb_mut_neuron_weight; // probability that one neuron's weight changes (0.0 - 1.0)
		double m_dProb_mut_output_weight; // probability that one output node's weight changes (0.0 - 1.0)

		/*activation function*/
		double m_dProb_mut_neuron_treshold; // probability that neuron's activation function's treshold changes (0.0 - 1.0)
		double m_dProb_mut_neuron_steepness; // probability that neuron's activation function's steepness changes (0.0 - 1.0)
		double m_dProb_mut_neuron_simetricity; // probability that neuron's activation function's simetricity changes (0.0 - 1.0)
		/*end activation function*/
	
	public:
		Mutation_params(const double prob_mut_neuron_weight = probabilityMinValue, const double prob_mut_output_weight = probabilityMinValue,
		const double prob_mut_neuron_treshold = probabilityMinValue, const double prob_mut_neuron_steepness = probabilityMinValue,
		const double prob_mut_neuron_simetricity = probabilityMinValue);

		double get_prob_mut_neuron_weight(void) const;
		double get_prob_mut_output_weight(void) const;
		double get_prob_mut_neuron_treshold(void) const;
		double get_prob_mut_neuron_steepness(void) const;
		double get_prob_mut_neuron_simetricity(void) const;

		void set_prob_mut_neuron_weight(double probability);
		void set_prob_mut_output_weight(double probability);
		void set_prob_mut_neuron_treshold(double probability);
		void set_prob_mut_neuron_steepness(double probability);
		void set_prob_mut_neuron_simetricity(double probability);
	};


	class Population
	{
	public:
		Mutation_params m_mutation_params; // mutation parameters
	
	private:
		std::vector<std::shared_ptr<Member>>& m_pMembers; // array of population members

	public:
		Population(std::vector<std::shared_ptr<Member>>& p_members);
		~Population(void);

		void calculate_outputs(void); // calculate output values of members
		void mutate(void); // mutate members of population
		void mate(void); // mate members of population, create new population

		void check_members(void); // check members for having correct parameters

	private:
		// mute one double value if the selection process (with given probability) is successful
		static double mutate_value(const double probability, const double min_value, const double max_value);

		unsigned long roulette_wheel(void) const; // roulette wheel selection algorithm
		unsigned long roulette_wheel(const unsigned long dropped_memb_indx) const; // roulette wheel selection algorithm
		unsigned long roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices) const; // roulette wheel selection algorithm
	};
};
