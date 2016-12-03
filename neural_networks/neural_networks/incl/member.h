#pragma once

#include "network.h"
#include "srestricted.h"
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
	public:
		Restricted_range::srestricted<double, 0, 1> m_dFitness; // fitness value (0.0 - 1.0)
		Network m_brain; // neural network, "the brain" of the population member
	public:
		Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs);
		virtual void reset(void); // reset member's fitness value and brain
		virtual void test(void) const; // test member's brain

		// used while creating new population
		static std::vector<std::shared_ptr<Member>> convert_to_pointers(std::vector<Member>& members);
	};
};