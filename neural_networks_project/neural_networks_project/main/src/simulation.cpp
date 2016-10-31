#include "simulation.h"

#include "population.h"
#include "rand_gen.h"

using namespace neural_networks;


void test_genetic_algorythm(void)
{
	Population test_population(2, 1, 1, 1, Mutation_params(0.2, 0.2, 0.2, 0.2, 0.2));

	for(unsigned long i = 0; i < test_population.m_members.size(); i++)
	{
		test_population.m_members[i].m_dFitness = random_double(0.0, 1.0);
	}

	test_population.mate();
	test_population.mutate();
}