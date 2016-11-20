#include "debug_population.h"
#include "debug_member.h"
#include "population.h"
#include "member.h"
#include <vector>
#include "rand_gen.h"
#include "restricted.h"
#include "srestricted.h"


namespace Neural_networks
{
	namespace Debug
	{
		static void test_constructor(void)
		{
			unsigned long N_members = random_unsigned_long(1, 10);
			unsigned long N_inputs = random_unsigned_long(1, 10);
			unsigned long N_neurons = random_unsigned_long(1, 10);
			unsigned long N_outputs = random_unsigned_long(1, 10);
			
			std::vector<Member> test_members1;
			test_members1.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members1.push_back(Member(N_inputs, N_neurons, N_outputs));
			}

			Population test_population1(test_members1, Mutation_params());
			test_population1.test();

			// if zero members
			std::vector<Member> test_members2;
			test_members2.clear();

			try
			{
				// this must throw an exception
				Population test_population2(test_members2, Mutation_params());
			}
			catch(...)
			{
				return;
			}
			throw Population_exception("Zero members in population. Check constructor.");
		}


		static void test_mutate_value(void)
		{
			const double min = random_double();
			const double max = min + abs(random_double());
			Restricted_range::restricted<double> value_to_randomize1(random_double(min, max), min, max);
			Population::mutate_value(random_double(0.0, 1.0), value_to_randomize1);

			Restricted_range::srestricted<double, 0, 1> value_to_randomize2(random_double(0.0, 1.0));
			Population::mutate_value(random_double(0.0, 1.0), value_to_randomize2);

			Restricted_range::srestricted<double, -1000, 1000> value_to_randomize3(random_double());
			Population::mutate_value(random_double(0.0, 1.0), value_to_randomize3);
		}


		static void test_calculation(void)
		{
			unsigned long N_members = random_unsigned_long(1, 10);
			unsigned long N_inputs = random_unsigned_long(1, 10);
			unsigned long N_neurons = random_unsigned_long(1, 10);
			unsigned long N_outputs = random_unsigned_long(1, 10);
			
			std::vector<Member> test_members;
			test_members.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members.push_back(Member(N_inputs, N_neurons, N_outputs));
			}

			Population test_population(test_members, Mutation_params());

			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				for(unsigned long j = 0; j < test_population.m_members[i].m_brain.m_dInputs.size(); j++)
				{
					test_population.m_members[i].m_brain.m_dInputs[j] = random_double(0.0, 1.0);
				}

				for(unsigned long j = 0; j < test_population.m_members[i].m_brain.m_neurons.size(); j++)
				{
					test_population.m_members[i].m_brain.m_neurons[j].m_dOutput = random_double(0.0, 1.0);
				}
			}

			test_population.calculate_outputs();

			test_population.m_members.clear();

			// if no members in population
			try
			{
				// this should throw an exception
				test_population.calculate_outputs();
			}
			catch(...)
			{
				return;
			}
			throw Population_exception("Zero members in population. Check calculation function.");
		}


		static void test_roulette_wheel(void)
		{
			unsigned long N_members = random_unsigned_long(1, 10);
			unsigned long N_inputs = random_unsigned_long(1, 10);
			unsigned long N_neurons = random_unsigned_long(1, 10);
			unsigned long N_outputs = random_unsigned_long(1, 10);
			
			std::vector<Member> test_members;
			test_members.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members.push_back(Member(N_inputs, N_neurons, N_outputs));
			}

			Population test_population(test_members, Mutation_params());

			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				test_population.m_members[i].m_dFitness = random_double(0.0, 1.0);
			}

			unsigned long indx = test_population.m_members.size();
			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				indx = test_population.roulette_wheel();
				if(indx >= test_population.m_members.size())
					throw Population_exception("Error in roulette wheel function.");
			}

			unsigned long dropped_indx = random_unsigned_long(0, test_population.m_members.size() - 1);
			for(unsigned long i = 0; i < test_population.m_members.size(); i++)
			{
				indx = test_population.roulette_wheel(dropped_indx);
				if((indx >= test_population.m_members.size()) ||
					((indx == dropped_indx) && (test_population.m_members.size() != 1)))
					throw Population_exception("Error in roulette wheel function.");
			}
		}


		void debug_population(void)
		{
			test_constructor();
			test_mutate_value();
			test_calculation();
			test_roulette_wheel();
		}
	};
};