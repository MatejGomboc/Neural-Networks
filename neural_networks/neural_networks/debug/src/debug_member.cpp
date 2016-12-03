#include "debug_member.h"
#include "debug_network.h"
#include "rand_gen.h"
#include "member.h"


namespace Neural_networks
{
	namespace Debug
	{
		void test_constructor(void)
		{
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_outputs = random_unsigned_long(1, 100);

			Member test_member(N_inputs, N_neurons, N_outputs);

			debug_member(N_inputs, N_neurons, N_outputs, test_member);
		}

		void test_if_equal(std::vector<std::shared_ptr<Member>>& p_members, std::vector<Member>& members)
		{
			for(unsigned long i = 0; i < members.size(); i++)
			{
				if(p_members[i]->m_dFitness != members[i].m_dFitness) throw(Member_exception("Error in Member::convert_to_pointers function."));

				for(unsigned long j = 0; j < members[i].m_brain.m_dInputs.size(); j++)
				{
					if(p_members[i]->m_brain.m_dInputs[j] != members[i].m_brain.m_dInputs[j])
						throw(Member_exception("Error in Member::convert_to_pointers function."));
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_neurons.size(); j++)
				{
					if(p_members[i]->m_brain.m_neurons[j].m_dOutput != members[i].m_brain.m_neurons[j].m_dOutput)
						throw(Member_exception("Error in Member::convert_to_pointers function."));

					if(p_members[i]->m_brain.m_neurons[j].m_dSimetricity != members[i].m_brain.m_neurons[j].m_dSimetricity)
						throw(Member_exception("Error in Member::convert_to_pointers function."));

					if(p_members[i]->m_brain.m_neurons[j].m_dSteepness != members[i].m_brain.m_neurons[j].m_dSteepness)
						throw(Member_exception("Error in Member::convert_to_pointers function."));

					if(p_members[i]->m_brain.m_neurons[j].m_dTreshold != members[i].m_brain.m_neurons[j].m_dTreshold)
						throw(Member_exception("Error in Member::convert_to_pointers function."));

					for(unsigned long k = 0; k < members[i].m_brain.m_neurons[j].m_vdWeights.size(); k++)
					{
						if(p_members[i]->m_brain.m_neurons[j].m_vdWeights[k] != members[i].m_brain.m_neurons[j].m_vdWeights[k])
							throw(Member_exception("Error in Member::convert_to_pointers function."));
					}
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_output_nodes.size(); j++)
				{
					for(unsigned long k = 0; k < members[i].m_brain.m_output_nodes[j].m_vdWeights.size(); k++)
					{
						if(p_members[i]->m_brain.m_output_nodes[j].m_vdWeights[k] != members[i].m_brain.m_output_nodes[j].m_vdWeights[k])
							throw(Member_exception("Error in Member::convert_to_pointers function."));
					}
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_dOutputs.size(); j++)
				{
					if(p_members[i]->m_brain.m_dOutputs[j] != members[i].m_brain.m_dOutputs[j])
						throw(Member_exception("Error in Member::convert_to_pointers function."));
				}
			}
		}

		void test_conversion_to_ptrs(void)
		{
			const unsigned long N_inputs = random_unsigned_long(1, 100);
			const unsigned long N_neurons = random_unsigned_long(1, 100);
			const unsigned long N_outputs = random_unsigned_long(1, 100);

			std::vector<Member> members;
			members.reserve(random_unsigned_long(1, 10));

			for(unsigned long i = 0; i < members.size(); i++)
			{
				members.push_back(Member(N_inputs, N_neurons, N_outputs));
			}

			std::vector<std::shared_ptr<Member>> p_members = Member::convert_to_pointers(members);

			test_if_equal(p_members, members);

			// randomize
			for(unsigned long i = 0; i < members.size(); i++)
			{
				members[i].m_dFitness = random_double(0.0, 1.0);

				for(unsigned long j = 0; j < members[i].m_brain.m_dInputs.size(); j++)
				{
					members[i].m_brain.m_dInputs[j] = random_double(0.0, 1.0);
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_neurons.size(); j++)
				{
					members[i].m_brain.m_neurons[j].m_dOutput = random_double(0.0, 1.0);

					members[i].m_brain.m_neurons[j].m_dSimetricity = random_double(0.0, 1.0);

					members[i].m_brain.m_neurons[j].m_dSteepness = random_double();

					members[i].m_brain.m_neurons[j].m_dTreshold = random_double(0.0, static_cast<double>(members[i].m_brain.m_neurons[j].m_vdWeights.size()));

					for(unsigned long k = 0; k < members[i].m_brain.m_neurons[j].m_vdWeights.size(); k++)
					{
						members[i].m_brain.m_neurons[j].m_vdWeights[k] = random_double(0.0, 1.0);
					}
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_output_nodes.size(); j++)
				{
					for(unsigned long k = 0; k < members[i].m_brain.m_output_nodes[j].m_vdWeights.size(); k++)
					{
						members[i].m_brain.m_output_nodes[j].m_vdWeights[k] = random_double(0.0, 1.0);
					}
				}

				for(unsigned long j = 0; j < members[i].m_brain.m_dOutputs.size(); j++)
				{
					members[i].m_brain.m_dOutputs[j] = random_double(0.0, 1.0);
				}
			}

			test_if_equal(p_members, members);
		}

		void debug_member(void)
		{
			test_constructor();
			test_conversion_to_ptrs();
		}


		void debug_member(const unsigned long N_inputs, const unsigned long N_neurons, const unsigned long N_outputs, Member& test_member)
		{
			debug_network(N_inputs, N_neurons, N_outputs, test_member.m_brain);
		}
	};
};