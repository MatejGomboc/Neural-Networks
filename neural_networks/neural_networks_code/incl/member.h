#pragma once

#include "network.h"
#include "neural_network_exception.h"

#include <vector>
#include <memory>


namespace Neural_networks
{
	class Member_exception: public Neural_network_exception
	{
	public:
		explicit Member_exception(const std::string message)
			: Neural_network_exception(message)
		{
		}
	};

	class Member
	{
	private:
		double m_dFitness; // fitness value (0.0 - 1.0)
	public:
		Network m_brain; // neural network, "the brain" of the population member
	public:
		Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);

		void set_fitness(const double new_fitness);
		double get_fitness(void);

		virtual void reset(void); // reset member's fitness value and brain
	};
};