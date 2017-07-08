#include "member.h"
#include "constants.h"


namespace Neural_networks
{
	Member::Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs)
		: m_brain(N_inputs, N_neurons, N_outputs), m_dFitness(fitnessMinValue)
	{
	}


	void Member::set_fitness(const double new_fitness)
	{
		if((new_fitness < fitnessMinValue) || (new_fitness > fitnessMaxValue)) throw Member_exception("New members's fitness has invalid value.");
		
		m_dFitness = new_fitness;
	}


	double Member::get_fitness(void)
	{
		return m_dFitness;
	}


	// reset member's fitness value and brain
	void Member::reset(void)
	{
		m_dFitness = fitnessMinValue;
		m_brain.reset();
	}
};