#include "debug_member.h"
#include "debug_network.h"
#include "rand_gen.h"
#include "member.h"


namespace Neural_networks
{
	namespace Debug
	{
		void debug_member(void)
		{
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_outputs = random_unsigned_long(1, 100);

			Member test_member(N_inputs, N_neurons, N_outputs);

			debug_member(N_inputs, N_neurons, N_outputs, test_member);
		}


		void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member)
		{
			debug_network(N_inputs, N_neurons, N_outputs, test_member.m_brain);
		}
	};
};