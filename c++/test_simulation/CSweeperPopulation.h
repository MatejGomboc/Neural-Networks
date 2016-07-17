#pragma once

//------------------------------------------------------------------------
//
//	Name: CSweeperPopulation.h
//
//  Desc: Class for the population of mine sweepers.
//
//------------------------------------------------------------------------

#include "../code/population.h"
#include "../code/member.h"
#include "CMineSweeper.h"
#include <vector>

class CSweeperPopulation : public neural_networks::population
{
public:
	double BestScore;
	double AverageScore;

	CSweeperPopulation(std::vector<neural_networks::member>::size_type N_members,
	std::vector<double>::size_type N_input_variables, std::vector<neural_networks::neuron>::size_type N_neurons,
	std::vector<double>::size_type N_output_variables, neural_networks::t_mut_params Mutation_params);

	~CSweeperPopulation(void);

	void CalculateBestWorstAverageIndxScore(void); // calculate best, worst and average fitnes, best and worst score and indices of fittest and weakest member
};

