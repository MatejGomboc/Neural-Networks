#pragma once

#include "member.h"


namespace neural_networks
{
	namespace debug
	{
		extern void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member);
		extern void debug_member(void);
	}
};