#include "debug_population.h"
#include "debug_member.h"
#include "population.h"
#include "member.h"
#include <vector>
#include <set>
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
			
			std::vector<std::shared_ptr<Member>> p_test_members1;
			p_test_members1.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				p_test_members1.push_back(std::shared_ptr<Member>(new Member(N_inputs, N_neurons, N_outputs)));
			}

			Population test_population1(p_test_members1, Mutation_params());
			test_population1.test();

			p_test_members1.push_back(std::shared_ptr<Member>(new Member(N_inputs, N_neurons, N_outputs)));
			if(p_test_members1.size() != test_population1.m_pMembers.size()) throw(new std::exception("Error in Population's constructor."));
			
			test_population1.m_pMembers[0]->m_dFitness = random_double(0.0, 1.0);
			if(test_population1.m_pMembers[0]->m_dFitness != p_test_members1[0]->m_dFitness) throw(new std::exception("Error in Population's constructor."));
			
			p_test_members1[0]->m_dFitness = random_double(0.0, 1.0);
			if(test_population1.m_pMembers[0]->m_dFitness != p_test_members1[0]->m_dFitness) throw(new std::exception("Error in Population's constructor."));

			// if zero members
			std::vector<std::shared_ptr<Member>> p_test_members2;
			p_test_members2.clear();

			try
			{
				// this must throw an exception
				Population test_population2(p_test_members2, Mutation_params());
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
			
			std::vector<std::shared_ptr<Member>> test_members;
			test_members.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members.push_back(std::shared_ptr<Member>(new Member(N_inputs, N_neurons, N_outputs)));
			}

			Population test_population(test_members, Mutation_params());

			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				for(unsigned long j = 0; j < test_population.m_pMembers[i]->m_brain.m_dInputs.size(); j++)
				{
					test_population.m_pMembers[i]->m_brain.m_dInputs[j] = random_double(0.0, 1.0);
				}

				for(unsigned long j = 0; j < test_population.m_pMembers[i]->m_brain.m_neurons.size(); j++)
				{
					test_population.m_pMembers[i]->m_brain.m_neurons[j].m_dOutput = random_double(0.0, 1.0);
				}
			}

			test_population.calculate_outputs();

			test_population.m_pMembers.clear();

			// if no members in population
			try
			{
				// this must throw an exception
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
			// prepare test population

			unsigned long N_members = random_unsigned_long(1, 10);
			unsigned long N_inputs = random_unsigned_long(1, 10);
			unsigned long N_neurons = random_unsigned_long(1, 10);
			unsigned long N_outputs = random_unsigned_long(1, 10);
			
			std::vector<std::shared_ptr<Member>> test_members;
			test_members.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members.push_back(std::shared_ptr<Member>(new Member(N_inputs, N_neurons, N_outputs)));
			}

			Population test_population(test_members, Mutation_params());

			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				test_population.m_pMembers[i]->m_dFitness = random_double(0.0, 1.0);
			}

			// test simple roulette wheel

			unsigned long indx = test_population.m_pMembers.size();
			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				indx = test_population.roulette_wheel();

				if(indx >= test_population.m_pMembers.size())
					throw Population_exception("Error in roulette wheel function.");
			}

			// test roulette wheel with one dropped index

			const unsigned long dropped_indx = random_unsigned_long(0, test_population.m_pMembers.size() - 1);
			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				indx = test_population.roulette_wheel(dropped_indx);

				if((indx >= test_population.m_pMembers.size()) ||
					((indx == dropped_indx) && (test_population.m_pMembers.size() > 1)))
					throw Population_exception("Error in roulette wheel function.");
			}

			// test roulette wheel with multiple dropped indices

			std::set<const unsigned long> dropped_indices;

			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				if(random_double(0.0, 1.0) <= 0.5) dropped_indices.insert(i);
			}

			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				indx = test_population.roulette_wheel(dropped_indices);

				if((indx >= test_population.m_pMembers.size()) ||
					((dropped_indices.find(indx) != dropped_indices.end())
					&& (test_population.m_pMembers.size() > 1)
					&& (test_population.m_pMembers.size() != dropped_indices.size())))
					throw Population_exception("Error in roulette wheel function.");
			}
		}


		void test_mutation_mating(void)
		{
			// prepare test population

			unsigned long N_members = random_unsigned_long(1, 10);
			unsigned long N_inputs = random_unsigned_long(1, 10);
			unsigned long N_neurons = random_unsigned_long(1, 10);
			unsigned long N_outputs = random_unsigned_long(1, 10);
			
			std::vector<std::shared_ptr<Member>> test_members;
			test_members.reserve(N_members);

			for(unsigned long i = 0; i < N_members; i++)
			{
				test_members.push_back(std::shared_ptr<Member>(new Member(N_inputs, N_neurons, N_outputs)));
			}

			Population test_population(test_members, Mutation_params());

			for(unsigned long i = 0; i < test_population.m_pMembers.size(); i++)
			{
				test_population.m_pMembers[i]->m_dFitness = random_double(0.0, 1.0);
			}


			// mutate members

			test_population.mutate();

			// mate members

			test_population.mate();
		}


		void debug_population(void)
		{
			test_constructor();
			test_mutate_value();
			test_calculation();
			test_roulette_wheel();
			test_mutation_mating();
		}
	};
};