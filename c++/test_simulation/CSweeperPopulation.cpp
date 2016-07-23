#include "CSweeperPopulation.h"
#include "../code/population.h"
#include "../code/member.h"
#include "../code/neuron.h"
#include "CMineSweeper.h"
#include <vector>

CSweeperPopulation::CSweeperPopulation(std::vector<neural_networks::member>::size_type N_members,
	std::vector<double>::size_type N_input_variables, std::vector<neural_networks::neuron>::size_type N_neurons,
	std::vector<double>::size_type N_output_variables, neural_networks::t_mut_params Mutation_params)
	: population(N_members, N_input_variables, N_neurons, N_output_variables, Mutation_params)
{
	BestScore = 0;
	AverageScore = 0;
}


CSweeperPopulation::~CSweeperPopulation(void)
{
}


void CSweeperPopulation::CalculateBestWorstAverageIndxScore(void)
{
	for (std::vector<neural_networks::member>::size_type i = 0; i < members.size(); ++i)
	{
		CMineSweeper sweeper = static_cast<CMineSweeper>(members[i]);
	}
}