#include "debug_member.h"
#include "debug_network.h"
#include "constants.h"
#include "rand_gen.h"
#include "member.h"

#include <vector>

namespace neural_networks
{
	namespace debug
	{
		extern void debug_member(void)
		{
			const unsigned long N_inputs = 10;
			const unsigned long N_neurons = 100;
			const unsigned long N_outputs = 5;

			Member test_member(N_inputs, N_neurons, N_outputs);

			debug_member(N_inputs, N_neurons, N_outputs, test_member);
		}


		extern void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member)
		{
			debug_network(N_inputs, N_neurons, N_outputs, test_member.m_brain);

			if((test_member.m_dFitness < 0.0) || (test_member.m_dFitness > 1.0)) throw "Invalid value of member's fitness.";
		}
	};
};