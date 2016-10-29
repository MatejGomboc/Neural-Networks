#pragma once

#include "network.h"
#include "restricted.h"


namespace neural_networks
{
	class Member : private IRestrictedRange<double>
	{
	public:
		restricted<double> m_dFitness; // fitness value (0.0 - 1.0)
		Network m_brain;               // neural network, "the brain" of the population member
	public:
		Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);
	};
};