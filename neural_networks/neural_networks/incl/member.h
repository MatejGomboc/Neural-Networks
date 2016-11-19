#pragma once

#include "network.h"
#include "srestricted.h"


namespace Neural_networks
{
	class Member
	{
	public:
		Restricted_range::srestricted<double, 0, 1> m_dFitness; // fitness value (0.0 - 1.0)
		Network m_brain; // neural network, "the brain" of the population member
	public:
		Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);
		virtual void reset(void); // reset member's fitness value and NN
	};
};