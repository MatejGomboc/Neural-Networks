#include "population.h"
#include "member.h"
#include "network.h"
#include "neuron.h"
#include "output_node.h"
#include "rand_gen.h"
#include "ptr_vector.h"

using namespace stdx;

neural_networks::population::population(std::vector<member>::size_type N_members, std::vector<double>::size_type N_input_variables, std::vector<neuron>::size_type N_neurons, std::vector<double>::size_type N_output_variables, t_mut_params Mutation_params)
{
	if (N_input_variables <= 0) throw "No member's input variables.";
	if (N_neurons <= 0) throw "Zero member's neurons.";
	if (N_output_variables <= 0) throw "No member's output variables.";
	if (N_members <= 0) throw "No members in this population.";

	if ((Mutation_params.mut_probability_activ_simetricity < 0.0) || (Mutation_params.mut_probability_activ_simetricity > 1.0))
		throw "Invalid probability that neuron's activation function's simetricity changes.";

	if ((Mutation_params.mut_probability_activ_steepness < 0.0) || (Mutation_params.mut_probability_activ_steepness > 1.0))
		throw "Invalid probability that neuron's activation function's steepness changes";

	if ((Mutation_params.mut_probability_activ_treshold < 0.0) || (Mutation_params.mut_probability_activ_treshold > 1.0))
		throw "Invalid probability that neuron's activation function's treshold changes";

	if ((Mutation_params.mut_probability_neuron_weight < 0.0) || (Mutation_params.mut_probability_neuron_weight > 1.0))
		throw "Invalid probability that one neuron's weight changes";

	if ((Mutation_params.mut_probability_output_weight < 0.0) || (Mutation_params.mut_probability_output_weight > 1.0))
		throw "Invalid probability that one output node's weight changes";

	members.reserve(N_members);

	for (std::vector<member>::size_type i = 0; i != N_members; i++)
	{
		members.push_back(member(N_input_variables, N_neurons, N_output_variables));
	}

	mutation_params = Mutation_params;

	WorstFitness = 0;
	AverageFitness = 0;

	indxFittestMember = 0;
	indxWeakestMember = 0;
}


neural_networks::population::~population(void)
{
	members.clear();
}


void neural_networks::population::calculate_outputs(void)
{
	for(std::vector<member>::size_type k = 0; k != members.size(); k++) // for each member in population
	{
		members[k].brain.calculate();
	}
}


void neural_networks::population::mutate(void)
{
	rand_gen Rand_gen;

	for(std::vector<member>::size_type k = 0; k != members.size(); k++) // for each member in population
	{
		for(std::vector<output_node>::size_type i = 0; i != members[k].brain.output_nodes.size(); i++) // for each output node
		{
			for(std::vector<double>::size_type j = 0; j != members[k].brain.output_nodes[i].weights.size(); j++) // for each weight
			{
				if(Rand_gen.random_double(0.0, 1.0) <= mutation_params.mut_probability_output_weight)
				{
					members[k].brain.output_nodes[i].weights[j] = Rand_gen.random_double(0.0, 1.0);
				}
			}
		}

		for(std::vector<neuron>::size_type i = 0; i != members[k].brain.neurons.size(); i++) // for each neuron
		{
			for(std::vector<double>::size_type j = 0; j != members[k].brain.neurons[i].weights.size(); j++) // for each weight
			{
				if(Rand_gen.random_double(0.0, 1.0) <= mutation_params.mut_probability_neuron_weight)
				{
					members[k].brain.neurons[i].weights[j] = Rand_gen.random_double(0.0, 1.0);
				}
			}

			if(Rand_gen.random_double(0.0, 1.0) <= mutation_params.mut_probability_activ_simetricity)
			{
				members[k].brain.neurons[i].simetricity = Rand_gen.random_double(0.0, 1.0);
			}

			if(Rand_gen.random_double(0.0, 1.0) <= mutation_params.mut_probability_activ_steepness)
			{
				members[k].brain.neurons[i].steepness = Rand_gen.random_double();
			}

			if(Rand_gen.random_double(0.0, 1.0) <= mutation_params.mut_probability_activ_treshold)
			{
				members[k].brain.neurons[i].treshold = Rand_gen.random_double(0.0, (double)(members[k].brain.neurons.size() + members[k].brain.inputs.size()));
			}
		}
	}
}


void neural_networks::population::mate(void)
{
	std::vector<member>::size_type i_ma = 0;
	std::vector<member>::size_type i_mb = 0;

	double mating_weight_a = 0.0;
	double mating_weight_b = 0.0;

	std::vector<member> new_members;
	new_members.reserve(members.size());

	for(std::vector<member>::size_type i_mn = 0; i_mn != new_members.size(); i_mn++)
	{
		i_ma = roulette_wheel();
		i_mb = roulette_wheel(i_ma);

		mating_weight_a = (members[i_ma].fitness == members[i_mb].fitness == 0.0) ? 1 : (members[i_ma].fitness / (members[i_ma].fitness + members[i_mb].fitness));
		mating_weight_b = (members[i_ma].fitness == members[i_mb].fitness == 0.0) ? 1 : (members[i_mb].fitness / (members[i_ma].fitness + members[i_mb].fitness));

		for(std::vector<output_node>::size_type i = 0; i != members[i_ma].brain.output_nodes.size(); i++) // for each output node
		{
			for(std::vector<double>::size_type j = 0; j != members[i_ma].brain.output_nodes[i].weights.size(); j++) // for each weight
			{
				new_members[i_mn].brain.output_nodes[i].weights[j] = mating_weight_a * (members[i_ma].brain.output_nodes[i].weights[j]) + mating_weight_b * (members[i_mb].brain.output_nodes[i].weights[j]);
			}
		}

		for(std::vector<neuron>::size_type i = 0; i != members[i_ma].brain.neurons.size(); i++) // for each neuron
		{
			for(std::vector<double>::size_type j = 0; j != members[i_ma].brain.neurons[i].weights.size(); j++) // for each weight
			{
				new_members[i_mn].brain.neurons[i].weights[j] = mating_weight_a * members[i_ma].brain.neurons[i].weights[j] + mating_weight_b * members[i_mb].brain.neurons[i].weights[j];
			}

			new_members[i_mn].brain.neurons[i].simetricity = mating_weight_a * members[i_ma].brain.neurons[i].simetricity + mating_weight_b * members[i_mb].brain.neurons[i].simetricity;

			new_members[i_mn].brain.neurons[i].steepness = mating_weight_a * members[i_ma].brain.neurons[i].steepness + mating_weight_b * members[i_mb].brain.neurons[i].steepness;

			new_members[i_mn].brain.neurons[i].treshold = mating_weight_a * members[i_ma].brain.neurons[i].treshold + mating_weight_b * members[i_mb].brain.neurons[i].treshold;

	    }
	}

	members.swap(new_members);
}


using namespace neural_networks;

std::vector<member>::size_type population::roulette_wheel(void)
{
	rand_gen Rand_gen;
	double total_fitness = 0.0;

	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
	{
		total_fitness += members[i].fitness;
	}

	double rndNumber = Rand_gen.random_double(0.0, total_fitness);
	double offset = 0.0;
	std::vector<member>::size_type pick = 0;

	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
	{
		offset += members[i].fitness;
		if (rndNumber <= offset) 
		{
			pick = i;
			break;
		}
	}

	return pick;
}


std::vector<member>::size_type population::roulette_wheel(std::vector<member>::size_type dropped_memb_indx)
{
	rand_gen Rand_gen;
	double total_fitness = 0.0;

	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
	{
		if(i != dropped_memb_indx) total_fitness += members[i].fitness;
	}

	double rndNumber = Rand_gen.random_double(0.0, total_fitness);
	double offset = 0.0;
	std::vector<member>::size_type pick = 0;

	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
	{
		if(i != dropped_memb_indx)
		{
			offset += members[i].fitness;
			if (rndNumber <= offset) 
			{
				pick = i;
				break;
			}
		}
	}

	return pick;
}


//std::vector<member>::size_type population::roulette_wheel(std::vector<std::vector<member>::size_type> dropped_memb_indx)
//{
//	rand_gen Rand_gen;
//	double total_fitness = 0.0;
//
//	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
//	{
//		if(is_in_array(i, dropped_memb_indx)) total_fitness += members[i].fitness;
//	}
//
//	double rndNumber = Rand_gen.random_double(0.0, total_fitness);
//	double offset = 0.0;
//	std::vector<member>::size_type pick = 0;
//
//	for (std::vector<member>::size_type i = 0; i != members.size(); i++) 
//	{
//		if(is_in_array(i, dropped_memb_indx))
//		{
//			offset += members[i].fitness;
//			if (rndNumber <= offset) 
//			{
//				pick = i;
//				break;
//			}
//		}
//	}
//
//	return pick;
//}


//bool is_in_array(std::vector<member>::size_type indx, std::vector<std::vector<member>::size_type> indx_array)
//{
//	if(indx_array.empty()) return false;
//	else
//	{
//		if(std::find(indx_array.begin(), indx_array.end(), indx) != indx_array.end()) return true;
//		else return false;
//	}
//}


void population::CalculateBestWorstAverageIndx(void)
{
	double HighestSoFar = 0;
	double LowestSoFar = 2.0;
	double TotalFitness = 0.0;
	
	for (std::vector<member>::size_type i = 0; i < members.size(); ++i)
	{
		//update fittest if necessary
		if (members[i].fitness > HighestSoFar)
		{
			HighestSoFar = members[i].fitness;
			indxFittestMember = i;
		}
		
		//update worst if necessary
		if (members[i].fitness < LowestSoFar)
		{
			LowestSoFar = members[i].fitness;
			WorstFitness = members[i].fitness;
			indxWeakestMember = i;
		}
		
		TotalFitness += members[i].fitness;
	}
	
	AverageFitness = TotalFitness / (double)members.size();
}