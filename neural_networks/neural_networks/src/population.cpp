#include "population.h"
#include "member.h"
#include "rand_gen.h"
#include "restricted.h"
#include "srestricted.h"
#include <vector>
#include <set>


namespace Neural_networks
{
	Mutation_params::Mutation_params(const double prob_mut_neuron_weight, const double prob_mut_output_weight,
		const double prob_mut_neuron_treshold, const double prob_mut_neuron_steepness,
		const double prob_mut_neuron_simetricity) :
		m_dProb_mut_neuron_weight(prob_mut_neuron_weight),
		m_dProb_mut_output_weight(prob_mut_output_weight),
		m_dProb_mut_neuron_treshold(prob_mut_neuron_treshold),
		m_dProb_mut_neuron_steepness(prob_mut_neuron_steepness),
		m_dProb_mut_neuron_simetricity(prob_mut_neuron_simetricity)
	{
	}


	Population::Population(std::vector<Member>& members, const Mutation_params& mutation_params) :
		m_members(members),
		m_mutation_params(mutation_params)
	{
		if (m_members.size() <= 0) throw Population_exception("Number of members in population cannot be zero.");

		for(unsigned long i = 0; i < m_members.size(); i++)
		{
			m_members[i].test();
		}
	}


	Population::~Population(void)
	{
		m_members.clear();
	}


	// check population for errors
	void Population::test(void) const
	{
		if (m_members.size() <= 0) throw Population_exception("No members in this population.");

		for(unsigned long i = 0; i < m_members.size(); i++)
		{
			m_members[i].test();
		}
	}


	void Population::calculate_outputs(void)
	{
		if (m_members.size() <= 0) throw Population_exception("No members in this population.");

		for(unsigned long k = 0; k < m_members.size(); k++) // for each member in population
		{
			m_members[k].m_brain.calculate();
		}
	}


	void Population::mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
		Restricted_range::restricted<double>& value_to_randomize)
	{
		if(random_double(0.0, 1.0) <= probability) // decission process with homogenous probability distribution
		{
			value_to_randomize = random_double(value_to_randomize.getMin(), value_to_randomize.getMax()); // if successfull, generate new value
		}
	}

	void Population::mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
		Restricted_range::srestricted<double, 0, 1>& value_to_randomize)
	{
		if(random_double(0.0, 1.0) <= probability) // decission process with homogenous probability distribution
		{
			value_to_randomize = random_double(value_to_randomize.getMin(), value_to_randomize.getMax()); // if successfull, generate new value
		}
	}

	void Population::mutate_value(const Restricted_range::srestricted<double, 0, 1> probability,
		Restricted_range::srestricted<double, -1000, 1000>& value_to_randomize)
	{
		if(random_double(0.0, 1.0) <= probability) // decission process with homogenous probability distribution
		{
			value_to_randomize = random_double(value_to_randomize.getMin(), value_to_randomize.getMax()); // if successfull, generate new value
		}
	}


	void Population::mutate(void)
	{
		test();

		for(unsigned long k = 0; k < m_members.size(); k++) // for each member in population
		{
			for(unsigned long i = 0; i < m_members[k].m_brain.m_output_nodes.size(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_members[k].m_brain.m_output_nodes[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_output_weight, m_members[k].m_brain.m_output_nodes[i].m_vdWeights[j]);
				}
			}

			for(unsigned long i = 0; i < m_members[k].m_brain.m_neurons.size(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_members[k].m_brain.m_neurons[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_neuron_weight, m_members[k].m_brain.m_neurons[i].m_vdWeights[j]);
				}

				mutate_value(m_mutation_params.m_dProb_mut_neuron_simetricity, m_members[k].m_brain.m_neurons[i].m_dSimetricity);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_steepness, m_members[k].m_brain.m_neurons[i].m_dSteepness);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_treshold, m_members[k].m_brain.m_neurons[i].m_dTreshold);
			}
		}

		test();
	}


	void Population::mate(void)
	{
		test();

		unsigned long i_ma = 0;
		unsigned long i_mb = 0;

		double mating_weight_a = 0.0;
		double mating_weight_b = 0.0;

		Member temp_member(m_members[0].m_brain.m_dInputs.size(), m_members[0].m_brain.m_neurons.size(), m_members[0].m_brain.m_dOutputs.size());

		std::vector<Member> new_members;
		new_members.reserve(m_members.size());

		for(unsigned long i_mn = 0; i_mn < m_members.size(); i_mn++) // for each population member
		{
			i_ma = roulette_wheel();
			i_mb = roulette_wheel(i_ma);

			mating_weight_a = (m_members[i_ma].m_dFitness == m_members[i_mb].m_dFitness == 0.0) ? 0.5 : (m_members[i_ma].m_dFitness / (m_members[i_ma].m_dFitness + m_members[i_mb].m_dFitness));
			mating_weight_b = (m_members[i_ma].m_dFitness == m_members[i_mb].m_dFitness == 0.0) ? 0.5 : (m_members[i_mb].m_dFitness / (m_members[i_ma].m_dFitness + m_members[i_mb].m_dFitness));

			for(unsigned long i = 0; i < m_members[i_ma].m_brain.m_output_nodes.size(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_members[i_ma].m_brain.m_output_nodes[i].m_vdWeights.size(); j++) // for each weight
				{
					temp_member.m_brain.m_output_nodes[i].m_vdWeights[j] = mating_weight_a * (m_members[i_ma].m_brain.m_output_nodes[i].m_vdWeights[j]) + mating_weight_b * (m_members[i_mb].m_brain.m_output_nodes[i].m_vdWeights[j]);
				}
			}

			for(unsigned long i = 0; i < m_members[i_ma].m_brain.m_neurons.size(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_members[i_ma].m_brain.m_neurons[i].m_vdWeights.size(); j++) // for each weight
				{
					temp_member.m_brain.m_neurons[i].m_vdWeights[j] = mating_weight_a * m_members[i_ma].m_brain.m_neurons[i].m_vdWeights[j] + mating_weight_b * m_members[i_mb].m_brain.m_neurons[i].m_vdWeights[j];
				}

				temp_member.m_brain.m_neurons[i].m_dSimetricity = mating_weight_a * m_members[i_ma].m_brain.m_neurons[i].m_dSimetricity + mating_weight_b * m_members[i_mb].m_brain.m_neurons[i].m_dSimetricity;

				temp_member.m_brain.m_neurons[i].m_dSteepness = mating_weight_a * m_members[i_ma].m_brain.m_neurons[i].m_dSteepness + mating_weight_b * m_members[i_mb].m_brain.m_neurons[i].m_dSteepness;

				temp_member.m_brain.m_neurons[i].m_dTreshold = mating_weight_a * m_members[i_ma].m_brain.m_neurons[i].m_dTreshold + mating_weight_b * m_members[i_mb].m_brain.m_neurons[i].m_dTreshold;

			}

			new_members.push_back(temp_member);
		}

		m_members.swap(new_members);

		test();
	}


	unsigned long Population::roulette_wheel(void) const // perform roulette wheel selection of population member
	{
		const double total_fitness = static_cast<double>(m_members.size());
		const double rand_num = random_double(0.0, total_fitness);

		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_members.size(); i++) 
		{
			offset += m_members[i].m_dFitness;
			if (rand_num <= offset) 
			{
				pick = i;
				break;
			}
		}

		return pick; // return indx of picked population member
	}


	// perform roulette wheel selection of population member
	unsigned long Population::roulette_wheel(const unsigned long dropped_memb_indx) const
	{
		if(dropped_memb_indx >= m_members.size())
			throw Population_exception("Invalid indx of dropped member in population during roulette wheel.");

		if(m_members.size() == 1) return 0;

		const double total_fitness = static_cast<double>(m_members.size()) - m_members[dropped_memb_indx].m_dFitness;
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_members.size(); i++) 
		{
			if(i != dropped_memb_indx)
			{
				offset += m_members[i].m_dFitness;
				if (rand_num <= offset) 
				{
					pick = i;
					break;
				}
			}
		}

		return pick; // return indx of picked population member
	}


	// perform roulette wheel selection of population member
	unsigned long Population::roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices) const
	{
		std::set<const unsigned long>::iterator it = --dropped_memb_indices.end();
		if(*it > m_members.size()) throw Population_exception("Invalid indx of dropped member in population during roulette wheel.");

		double total_fitness = static_cast<double>(m_members.size());
	
		for (std::set<const unsigned long>::iterator it = dropped_memb_indices.begin(); it != dropped_memb_indices.end(); it++) 
		{
			total_fitness -= m_members[*it].m_dFitness;
		}
	
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;
	
		for (unsigned long i = 0; i < m_members.size(); i++) 
		{
			if(dropped_memb_indices.find(i) != dropped_memb_indices.end())
			{
				offset += m_members[i].m_dFitness;
				if (rand_num <= offset) 
				{
					pick = i;
					break;
				}
			}
		}
	
		return pick; // return indx of picked population member
	}
};