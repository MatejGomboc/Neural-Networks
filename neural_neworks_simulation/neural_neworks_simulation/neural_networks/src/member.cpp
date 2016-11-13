#include "member.h"
#include "constants.h"


namespace neural_networks
{
	Member::Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs)
		: m_brain(N_inputs, N_neurons, N_outputs), m_dFitness(0.0)
	{
	}


	// reset member's fitness value and NN
	void Member::reset(void)
	{
		m_dFitness = 0.0;
		m_brain.reset();
	}
};