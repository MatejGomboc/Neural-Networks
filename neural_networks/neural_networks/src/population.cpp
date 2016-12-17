#include "population.h"
#include "member.h"
#include "rand_gen.h"
#include "restricted.h"
#include "srestricted.h"
#include <vector>
#include <set>

#include "mine_sweeper.h"

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


	Population::Population(std::vector<std::shared_ptr<Member>>& p_members, const Mutation_params& mutation_params) :
		m_pMembers(p_members),
		m_mutation_params(mutation_params)
	{
		if (m_pMembers.size() <= 0) throw Population_exception("Number of members in population cannot be zero.");

		for(unsigned long i = 0; i < p_members.size(); i++)
		{
			if(m_pMembers[i] == nullptr) throw Population_exception("Not a pointer to a member of population.");
			m_pMembers[i]->test();
		}
	}


	Population::~Population(void)
	{
		m_pMembers.clear();
	}


	// check population for errors
	void Population::test(void) const
	{
		if (m_pMembers.size() <= 0) throw Population_exception("No members in this population.");

		for(unsigned long i = 0; i < m_pMembers.size(); i++)
		{
			m_pMembers[i]->test();
		}
	}


	void Population::calculate_outputs(void)
	{
		if (m_pMembers.size() <= 0) throw Population_exception("No members in this population.");

		for(unsigned long k = 0; k < m_pMembers.size(); k++) // for each member in population
		{
			m_pMembers[k]->m_brain.calculate();
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

		for(unsigned long k = 0; k < m_pMembers.size(); k++) // for each member in population
		{
			for(unsigned long i = 0; i < m_pMembers[k]->m_brain.m_output_nodes.size(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_pMembers[k]->m_brain.m_output_nodes[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_output_weight, m_pMembers[k]->m_brain.m_output_nodes[i].m_vdWeights[j]);
				}
			}

			for(unsigned long i = 0; i < m_pMembers[k]->m_brain.m_neurons.size(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_pMembers[k]->m_brain.m_neurons[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_neuron_weight, m_pMembers[k]->m_brain.m_neurons[i].m_vdWeights[j]);
				}

				mutate_value(m_mutation_params.m_dProb_mut_neuron_simetricity, m_pMembers[k]->m_brain.m_neurons[i].m_dSimetricity);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_steepness, m_pMembers[k]->m_brain.m_neurons[i].m_dSteepness);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_treshold, m_pMembers[k]->m_brain.m_neurons[i].m_dTreshold);
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

		std::shared_ptr<Member> temp_member(new Member(m_pMembers[0]->m_brain.m_dInputs.size(), m_pMembers[0]->m_brain.m_neurons.size(), m_pMembers[0]->m_brain.m_dOutputs.size()));

		std::vector<std::shared_ptr<Member>> new_members;
		new_members.reserve(m_pMembers.size());

		for(unsigned long i_mn = 0; i_mn < m_pMembers.size(); i_mn++) // for each population member
		{
			i_ma = roulette_wheel();
			i_mb = roulette_wheel(i_ma);

			mating_weight_a = (m_pMembers[i_ma]->m_dFitness == m_pMembers[i_mb]->m_dFitness == 0.0) ? 0.5 : (m_pMembers[i_ma]->m_dFitness / (m_pMembers[i_ma]->m_dFitness + m_pMembers[i_mb]->m_dFitness));
			//mating_weight_b = (m_pMembers[i_ma]->m_dFitness == m_pMembers[i_mb]->m_dFitness == 0.0) ? 0.5 : (m_pMembers[i_mb]->m_dFitness / (m_pMembers[i_ma]->m_dFitness + m_pMembers[i_mb]->m_dFitness));

			for(unsigned long i = 0; i < m_pMembers[i_ma]->m_brain.m_output_nodes.size(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_pMembers[i_ma]->m_brain.m_output_nodes[i].m_vdWeights.size(); j++) // for each weight
				{
					//temp_member->m_brain.m_output_nodes[i].m_vdWeights[j] = mating_weight_a * (m_pMembers[i_ma]->m_brain.m_output_nodes[i].m_vdWeights[j]) + mating_weight_b * (m_pMembers[i_mb]->m_brain.m_output_nodes[i].m_vdWeights[j]);
					temp_member->m_brain.m_output_nodes[i].m_vdWeights[j] = (random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.m_output_nodes[i].m_vdWeights[j]) : (m_pMembers[i_mb]->m_brain.m_output_nodes[i].m_vdWeights[j]);
				}
			}

			for(unsigned long i = 0; i < m_pMembers[i_ma]->m_brain.m_neurons.size(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_pMembers[i_ma]->m_brain.m_neurons[i].m_vdWeights.size(); j++) // for each weight
				{
					//temp_member->m_brain.m_neurons[i].m_vdWeights[j] = mating_weight_a * m_pMembers[i_ma]->m_brain.m_neurons[i].m_vdWeights[j] + mating_weight_b * m_pMembers[i_mb]->m_brain.m_neurons[i].m_vdWeights[j];
					temp_member->m_brain.m_neurons[i].m_vdWeights[j] = (random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.m_neurons[i].m_vdWeights[j]) : (m_pMembers[i_mb]->m_brain.m_neurons[i].m_vdWeights[j]);
				}

				//temp_member->m_brain.m_neurons[i].m_dSimetricity = mating_weight_a * m_pMembers[i_ma]->m_brain.m_neurons[i].m_dSimetricity + mating_weight_b * m_pMembers[i_mb]->m_brain.m_neurons[i].m_dSimetricity;
				temp_member->m_brain.m_neurons[i].m_dSimetricity = (random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.m_neurons[i].m_dSimetricity) : (mating_weight_b * m_pMembers[i_mb]->m_brain.m_neurons[i].m_dSimetricity);

				//temp_member->m_brain.m_neurons[i].m_dSteepness = mating_weight_a * m_pMembers[i_ma]->m_brain.m_neurons[i].m_dSteepness + mating_weight_b * m_pMembers[i_mb]->m_brain.m_neurons[i].m_dSteepness;
				temp_member->m_brain.m_neurons[i].m_dSteepness = (random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.m_neurons[i].m_dSteepness) : (m_pMembers[i_mb]->m_brain.m_neurons[i].m_dSteepness);

				//temp_member->m_brain.m_neurons[i].m_dTreshold = mating_weight_a * m_pMembers[i_ma]->m_brain.m_neurons[i].m_dTreshold + mating_weight_b * m_pMembers[i_mb]->m_brain.m_neurons[i].m_dTreshold;
				temp_member->m_brain.m_neurons[i].m_dTreshold = (random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.m_neurons[i].m_dTreshold) : (m_pMembers[i_mb]->m_brain.m_neurons[i].m_dTreshold);
			}

			new_members.push_back(temp_member);
		}

		m_pMembers.swap(new_members);

		test();
	}


	unsigned long Population::roulette_wheel(void) const // perform roulette wheel selection of population member
	{
		double total_fitness = 0.0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			total_fitness += m_pMembers[i]->m_dFitness;
		}

		const double rand_num = random_double(0.0, total_fitness);

		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			offset += m_pMembers[i]->m_dFitness;
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
		if(dropped_memb_indx >= m_pMembers.size())
			throw Population_exception("Index of dropped member must be contained in population.");

		if(m_pMembers.size() == 1) return 0;
		else if(m_pMembers.size() == 2)
		{
			for (unsigned long i = 0; i < 2; i++) 
			{
				if(i != dropped_memb_indx) return i;
			}
		}

		double total_fitness = 0.0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			total_fitness += m_pMembers[i]->m_dFitness;
		}

		total_fitness -= m_pMembers[dropped_memb_indx]->m_dFitness;
		
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(i != dropped_memb_indx)
			{
				offset += m_pMembers[i]->m_dFitness;
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
		if(dropped_memb_indices.size() > 0)
		{
			// iterator pointing to the last (the largest) value contained in set
			if(*(--dropped_memb_indices.end()) >= m_pMembers.size()) throw Population_exception("Index of dropped member must be contained in population.");
		}

		if(m_pMembers.size() == 1) return 0;

		double total_fitness = 0.0;
	
		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(dropped_memb_indices.find(i) == dropped_memb_indices.end()) // index NOT contained in set
			{
				total_fitness += m_pMembers[i]->m_dFitness;
			}
		}
	
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;
	
		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(dropped_memb_indices.find(i) == dropped_memb_indices.end()) // if index NOT contained in set
			{
				offset += m_pMembers[i]->m_dFitness;
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