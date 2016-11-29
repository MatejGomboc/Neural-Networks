#include "member.h"


namespace Neural_networks
{
	Member::Member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs)
		: m_brain(N_inputs, N_neurons, N_outputs), m_dFitness(0.0)
	{
	}


	// reset member's fitness value and brain
	void Member::reset(void)
	{
		m_dFitness = 0.0;
		m_brain.reset();
	}


	// test member's brain
	void Member::test(void) const
	{
		m_brain.test();
	}


	std::vector<std::shared_ptr<Member>> Member::convert_to_pointers(std::vector<Member>& members)
	{
		std::vector<std::shared_ptr<Member>> p_members;
		p_members.reserve(members.size());

		for (unsigned long i = 0; i < members.size(); i++)
		{
			p_members.push_back(std::shared_ptr<Member>(&members[i]));
		}

		return p_members;
	}
};