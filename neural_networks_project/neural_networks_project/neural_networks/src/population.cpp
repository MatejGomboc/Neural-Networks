#include "population.h"
#include "member.h"
#include "rand_gen.h"
#include <vector>
#include <set>


namespace neural_networks
{
	Mutation_params::Mutation_params(void) :
		m_dProb_mut_neuron_weight(probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_output_weight(probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_treshold(probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_steepness(probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_simetricity(probabilityMinValue, probabilityMaxValue)
	{
	}


	Mutation_params::Mutation_params(const double prob_mut_neuron_weight, const double prob_mut_output_weight,
		const double prob_mut_neuron_treshold, double prob_mut_neuron_steepness, double prob_mut_neuron_simetricity) :
		m_dProb_mut_neuron_weight(prob_mut_neuron_weight, probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_output_weight(prob_mut_output_weight, probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_treshold(prob_mut_neuron_treshold, probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_steepness(prob_mut_neuron_steepness, probabilityMinValue, probabilityMaxValue),
		m_dProb_mut_neuron_simetricity(prob_mut_neuron_simetricity, probabilityMinValue, probabilityMaxValue)
	{
	}


	Population::Population(const unsigned long N_members, const unsigned long N_memb_input_variables, const unsigned long N_memb_neurons,
			const unsigned long N_memb_output_variables, const Mutation_params& mutation_params)
	{
		if (N_members <= 0) throw "No members in this population.";
		if (N_memb_input_variables <= 0) throw "No member's input variables.";
		if (N_memb_neurons <= 0) throw "Zero member's neurons.";
		if (N_memb_output_variables <= 0) throw "No member's output variables.";

		if ((mutation_params.m_dProb_mut_neuron_simetricity < 0.0) || (mutation_params.m_dProb_mut_neuron_simetricity > 1.0))
			throw "Invalid probability that neuron's activation function's simetricity changes.";

		if ((mutation_params.m_dProb_mut_neuron_steepness < 0.0) || (mutation_params.m_dProb_mut_neuron_steepness > 1.0))
			throw "Invalid probability that neuron's activation function's steepness changes";

		if ((mutation_params.m_dProb_mut_neuron_treshold < 0.0) || (mutation_params.m_dProb_mut_neuron_treshold > 1.0))
			throw "Invalid probability that neuron's activation function's treshold changes";

		if ((mutation_params.m_dProb_mut_neuron_weight < 0.0) || (mutation_params.m_dProb_mut_neuron_weight > 1.0))
			throw "Invalid probability that one neuron's weight changes";

		if ((mutation_params.m_dProb_mut_output_weight < 0.0) || (mutation_params.m_dProb_mut_output_weight > 1.0))
			throw "Invalid probability that one output node's weight changes";

		m_members.reserve(N_members);

		for (unsigned long i = 0; i < N_members; i++)
		{
			m_members.push_back(Member(N_memb_input_variables, N_memb_neurons, N_memb_output_variables));
		}

		m_mutation_params = mutation_params;
	}


	Population::~Population(void)
	{
		m_members.clear();
	}


	void Population::calculate_outputs(void)
	{
		for(unsigned long k = 0; k < m_members.size(); k++) // for each member in population
		{
			m_members[k].m_brain.calculate();
		}
	}


	void Population::mutate_value(const double probability, const double min, const double max, restricted<double>& value_to_randomize)
	{
		if(random_double(0.0, 1.0) <= probability) // decission process with homogenous probability distribution
		{
			value_to_randomize = random_double(min, max); // if successfull, generate new value
		}
	}


	void Population::mutate(void)
	{
		for(unsigned long k = 0; k < m_members.size(); k++) // for each member in population
		{
			for(unsigned long i = 0; i < m_members[k].m_brain.m_output_nodes.size(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_members[k].m_brain.m_output_nodes[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_output_weight, weightMinValue, weightMaxValue,
						m_members[k].m_brain.m_output_nodes[i].m_vdWeights[j]);
				}
			}

			for(unsigned long i = 0; i < m_members[k].m_brain.m_neurons.size(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_members[k].m_brain.m_neurons[i].m_vdWeights.size(); j++) // for each weight
				{
					mutate_value(m_mutation_params.m_dProb_mut_neuron_weight, weightMinValue, weightMaxValue,
						m_members[k].m_brain.m_neurons[i].m_vdWeights[j]);
				}

				mutate_value(m_mutation_params.m_dProb_mut_neuron_simetricity, simetricityMinValue, simetricityMaxValue,
					m_members[k].m_brain.m_neurons[i].m_dSimetricity);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_steepness, steepnessMinValue, steepnessMaxValue,
					m_members[k].m_brain.m_neurons[i].m_dSteepness);

				mutate_value(m_mutation_params.m_dProb_mut_neuron_treshold, tresholdMinValue,
					m_members[k].m_brain.m_neurons[i].m_dTreshold.getMax(),
					m_members[k].m_brain.m_neurons[i].m_dTreshold);
			}
		}
	}


	//void neural_networks::population::mate(void)
	//{
	//	std::vector<member>::size_type i_ma = 0;
	//	std::vector<member>::size_type i_mb = 0;

	//	double mating_weight_a = 0.0;
	//	double mating_weight_b = 0.0;

	//	std::vector<member> new_members;
	//	new_members.reserve(members.size());

	//	for(std::vector<member>::size_type i_mn = 0; i_mn != new_members.size(); i_mn++)
	//	{
	//		i_ma = roulette_wheel();
	//		i_mb = roulette_wheel(i_ma);

	//		mating_weight_a = (members[i_ma].fitness == members[i_mb].fitness == 0.0) ? 1 : (members[i_ma].fitness / (members[i_ma].fitness + members[i_mb].fitness));
	//		mating_weight_b = (members[i_ma].fitness == members[i_mb].fitness == 0.0) ? 1 : (members[i_mb].fitness / (members[i_ma].fitness + members[i_mb].fitness));

	//		for(std::vector<output_node>::size_type i = 0; i != members[i_ma].brain.output_nodes.size(); i++) // for each output node
	//		{
	//			for(std::vector<double>::size_type j = 0; j != members[i_ma].brain.output_nodes[i].weights.size(); j++) // for each weight
	//			{
	//				new_members[i_mn].brain.output_nodes[i].weights[j] = mating_weight_a * (members[i_ma].brain.output_nodes[i].weights[j]) + mating_weight_b * (members[i_mb].brain.output_nodes[i].weights[j]);
	//			}
	//		}

	//		for(std::vector<neuron>::size_type i = 0; i != members[i_ma].brain.neurons.size(); i++) // for each neuron
	//		{
	//			for(std::vector<double>::size_type j = 0; j != members[i_ma].brain.neurons[i].weights.size(); j++) // for each weight
	//			{
	//				new_members[i_mn].brain.neurons[i].weights[j] = mating_weight_a * members[i_ma].brain.neurons[i].weights[j] + mating_weight_b * members[i_mb].brain.neurons[i].weights[j];
	//			}

	//			new_members[i_mn].brain.neurons[i].simetricity = mating_weight_a * members[i_ma].brain.neurons[i].simetricity + mating_weight_b * members[i_mb].brain.neurons[i].simetricity;

	//			new_members[i_mn].brain.neurons[i].steepness = mating_weight_a * members[i_ma].brain.neurons[i].steepness + mating_weight_b * members[i_mb].brain.neurons[i].steepness;

	//			new_members[i_mn].brain.neurons[i].treshold = mating_weight_a * members[i_ma].brain.neurons[i].treshold + mating_weight_b * members[i_mb].brain.neurons[i].treshold;

	//		}
	//	}

	//	members.swap(new_members);
	//}


	const unsigned long Population::roulette_wheel(void) // perform roulette wheel selection of population member
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
	const unsigned long Population::roulette_wheel(const unsigned long dropped_memb_indx)
	{
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
	const unsigned long Population::roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices)
	{
		std::set<const unsigned long>::iterator it = --dropped_memb_indices.end();
		if(*it > m_members.size()) throw "Invalid indx of dropped member in population during roulette wheel.";

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