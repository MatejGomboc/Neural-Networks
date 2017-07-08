#include "population.h"
#include "member.h"
#include "rand_gen.h"

#include <vector>
#include <set>


namespace Neural_networks
{
	Mutation_params::Mutation_params(const double prob_mut_neuron_weight, const double prob_mut_output_weight,
		const double prob_mut_neuron_treshold, const double prob_mut_neuron_steepness,
		const double prob_mut_neuron_simetricity) :
		m_dProb_mut_neuron_weight(prob_mut_neuron_weight),
		m_dProb_mut_output_weight(prob_mut_output_weight),
		m_dProb_mut_neuron_treshold(prob_mut_neuron_treshold),
		m_dProb_mut_neuron_steepness(prob_mut_neuron_steepness),
		m_dProb_mut_neuron_simetricity(prob_mut_neuron_simetricity)
	{
	}


	double Mutation_params::get_prob_mut_neuron_weight(void) const
	{
		return m_dProb_mut_neuron_weight;
	}

	double Mutation_params::get_prob_mut_output_weight(void) const
	{
		return m_dProb_mut_output_weight;
	}

	double Mutation_params::get_prob_mut_neuron_treshold(void) const
	{
		return m_dProb_mut_neuron_treshold;
	}

	double Mutation_params::get_prob_mut_neuron_steepness(void) const
	{
		return m_dProb_mut_neuron_steepness;
	}

	double Mutation_params::get_prob_mut_neuron_simetricity(void) const
	{
		return m_dProb_mut_neuron_simetricity;
	}

	void Mutation_params::set_prob_mut_neuron_weight(double probability)
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability value.");

		m_dProb_mut_neuron_weight = probability;
	}

	void Mutation_params::set_prob_mut_output_weight(double probability)
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability value.");

		m_dProb_mut_output_weight = probability;
	}

	void Mutation_params::set_prob_mut_neuron_treshold(double probability)
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability value.");

		m_dProb_mut_neuron_treshold = probability;
	}

	void Mutation_params::set_prob_mut_neuron_steepness(double probability)
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability value.");

		m_dProb_mut_neuron_steepness = probability;
	}

	void Mutation_params::set_prob_mut_neuron_simetricity(double probability)
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability value.");

		m_dProb_mut_neuron_simetricity = probability;
	}



	Population::Population(std::vector<std::shared_ptr<Member>>& p_members) :
		m_pMembers(p_members)
	{
	}


	Population::~Population(void)
	{
		m_pMembers.clear();
	}


	void Population::check_members(void)
	{
		if (m_pMembers.size() < 2) throw Population_exception("There should be at least 2 members in population.");

		for(unsigned long i = 0; i < m_pMembers.size(); i++)
		{
			if(m_pMembers[i] == nullptr) throw Population_exception("Population member null pointer error.");

			if(i > 0)
			{
				if(m_pMembers[i]->m_brain.get_num_inputs() != m_pMembers[i-1]->m_brain.get_num_inputs())
					throw Population_exception("Population members have different number of network inputs.");

				if(m_pMembers[i]->m_brain.get_num_neurons() != m_pMembers[i-1]->m_brain.get_num_neurons())
					throw Population_exception("Population members have different number of neurons.");

				if(m_pMembers[i]->m_brain.get_num_output_nodes() != m_pMembers[i-1]->m_brain.get_num_output_nodes())
					throw Population_exception("Population members have different number of output nodes.");

				if(m_pMembers[i]->m_brain.get_num_outputs() != m_pMembers[i-1]->m_brain.get_num_outputs())
					throw Population_exception("Population members have different number of network outputs.");

				for (unsigned long j = 0; j < m_pMembers[i]->m_brain.get_num_neurons(); j++)
				{
					if(m_pMembers[i]->m_brain.get_neuron_weights_length(j) != m_pMembers[i-1]->m_brain.get_neuron_weights_length(j))
						throw Population_exception("Population members have different number of neuron weights.");
				}

				for (unsigned long j = 0; j < m_pMembers[i]->m_brain.get_num_output_nodes(); j++)
				{
					if(m_pMembers[i]->m_brain.get_output_node_weights_length(j) != m_pMembers[i-1]->m_brain.get_output_node_weights_length(j))
						throw Population_exception("Population members have different number of output node weights.");
				}
			}
		}
	}


	void Population::calculate_outputs(void)
	{
		check_members();

		for(unsigned long i = 0; i < m_pMembers.size(); i++) // for each member in population
		{
			m_pMembers[i]->m_brain.calculate();
		}
	}


	double Population::mutate_value(const double probability, const double min_value, const double max_value, )
	{
		if ((probability < probabilityMinValue) || (probability > probabilityMaxValue)) throw Population_exception("Invalid probability of value mutation");
		if (min_value > max_value) throw Population_exception("Lower mutation limit greater than upper mutation limit.");

		if(random_double(0.0, 1.0) <= probability) // decission process with homogenous probability distribution
		{
			return random_double(min_value, max_value); // if successfull, generate new value
		}
	}


	void Population::mutate(void)
	{
		check_members();

		for(unsigned long k = 0; k < m_pMembers.size(); k++) // for each member in population
		{
			for(unsigned long i = 0; i < m_pMembers[k]->m_brain.get_num_output_nodes(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_pMembers[k]->m_brain.get_output_node_weights_length(i); j++) // for each weight
				{
					m_pMembers[k]->m_brain.set_output_node_weight(mutate_value(m_mutation_params.get_prob_mut_output_weight(), weightMinValue, weightMaxValue), i, j);
				}
			}

			for(unsigned long i = 0; i < m_pMembers[k]->m_brain.get_num_neurons(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_pMembers[k]->m_brain.get_neuron_weights_length(i); j++) // for each weight
				{
					m_pMembers[k]->m_brain.set_neuron_weight(mutate_value(m_mutation_params.get_prob_mut_neuron_weight(), weightMinValue, weightMaxValue), i, j);
				}

				m_pMembers[k]->m_brain.set_neuron_simetricity(mutate_value(m_mutation_params.get_prob_mut_neuron_simetricity(), simetricityMinValue, simetricityMaxValue), i);

				m_pMembers[k]->m_brain.set_neuron_steepness(mutate_value(m_mutation_params.get_prob_mut_neuron_steepness(), steepnessMinValue, steepnessMaxValue), i);

				m_pMembers[k]->m_brain.set_neuron_treshold(mutate_value(m_mutation_params.get_prob_mut_neuron_treshold(), tresholdMinValue, static_cast<double>(m_pMembers[k]->m_brain.get_num_neurons() + m_pMembers[k]->m_brain.get_num_inputs())), i);
			}
		}
	}


	void Population::mate(void)
	{
		check_members();

		unsigned long i_ma = 0;
		unsigned long i_mb = 0;

		double mating_weight_a = 0.0;
		double mating_weight_b = 0.0;

		std::shared_ptr<Member> temp_member(new Member(m_pMembers[0]->m_brain.get_num_inputs(), m_pMembers[0]->m_brain.get_num_neurons(), m_pMembers[0]->m_brain.get_num_outputs()));

		std::vector<std::shared_ptr<Member>> new_members;
		new_members.reserve(m_pMembers.size());

		for(unsigned long i_mn = 0; i_mn < m_pMembers.size(); i_mn++) // for each population member
		{
			i_ma = roulette_wheel();
			i_mb = roulette_wheel(i_ma);

			mating_weight_a = (m_pMembers[i_ma]->get_fitness() == m_pMembers[i_mb]->get_fitness() == 0.0) ? 0.5 : (m_pMembers[i_ma]->get_fitness() / (m_pMembers[i_ma]->get_fitness() + m_pMembers[i_mb]->get_fitness()));
			//mating_weight_b = (m_pMembers[i_ma]->get_fitness() == m_pMembers[i_mb]->get_fitness() == 0.0) ? 0.5 : (m_pMembers[i_mb]->get_fitness() / (m_pMembers[i_ma]->get_fitness() + m_pMembers[i_mb]->get_fitness()));

			for(unsigned long i = 0; i < m_pMembers[i_ma]->m_brain.get_num_output_nodes(); i++) // for each output node
			{
				for(unsigned long j = 0; j < m_pMembers[i_ma]->m_brain.get_output_node_weights_length(i); j++) // for each weight
				{
					//temp_member->m_brain.set_output_node_weight(mating_weight_a * m_pMembers[i_ma]->m_brain.get_output_node_weight(i, j) + mating_weight_b * m_pMembers[i_mb]->m_brain.get_output_node_weight(i, j), i, j);
					temp_member->m_brain.set_output_node_weight((random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.get_output_node_weight(i, j)) : (m_pMembers[i_mb]->m_brain.get_output_node_weight(i, j)), i, j);
				}
			}

			for(unsigned long i = 0; i < m_pMembers[i_ma]->m_brain.get_num_neurons(); i++) // for each neuron
			{
				for(unsigned long j = 0; j < m_pMembers[i_ma]->m_brain.get_neuron_weights_length(i); j++) // for each weight
				{
					//temp_member->m_brain.set_neuron_weight(mating_weight_a * m_pMembers[i_ma]->m_brain.get_neuron_weight(i, j) + mating_weight_b * m_pMembers[i_mb]->m_brain.get_neuron_weight(i, j), i, j);
					temp_member->m_brain.set_neuron_weight((random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.get_neuron_weight(i, j)) : (m_pMembers[i_mb]->m_brain.get_neuron_weight(i, j)), i, j);
				}

				//temp_member->m_brain.set_neuron_simetricity(mating_weight_a * m_pMembers[i_ma]->m_brain.get_neuron_simetricity(i) + mating_weight_b * m_pMembers[i_mb]->m_brain.get_neuron_simetricity(i), i);
				temp_member->m_brain.set_neuron_simetricity((random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.get_neuron_simetricity(i)) : (mating_weight_b * m_pMembers[i_mb]->m_brain.get_neuron_simetricity(i)), i);

				//temp_member->m_brain.set_neuron_steepness(mating_weight_a * m_pMembers[i_ma]->m_brain.get_neuron_steepness(i) + mating_weight_b * m_pMembers[i_mb]->m_brain.get_neuron_steepness(i), i);
				temp_member->m_brain.set_neuron_steepness((random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.get_neuron_steepness(i)) : (m_pMembers[i_mb]->m_brain.get_neuron_steepness(i)), i);

				//temp_member->m_brain.set_neuron_treshold(mating_weight_a * m_pMembers[i_ma]->m_brain.get_neuron_treshold(i) + mating_weight_b * m_pMembers[i_mb]->m_brain.get_neuron_treshold(i), i);
				temp_member->m_brain.set_neuron_treshold((random_double(0.0, 1.0) <= mating_weight_a) ? (m_pMembers[i_ma]->m_brain.get_neuron_treshold(i)) : (m_pMembers[i_mb]->m_brain.get_neuron_treshold(i)), i);
			}

			new_members.push_back(temp_member);
		}

		m_pMembers.swap(new_members);
	}


	unsigned long Population::roulette_wheel(void) const // perform roulette wheel selection of population member
	{
		double total_fitness = 0.0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			total_fitness += m_pMembers[i]->get_fitness();
		}

		const double rand_num = random_double(0.0, total_fitness);

		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			offset += m_pMembers[i]->get_fitness();
			if (rand_num <= offset) 
			{
				pick = i;
				break;
			}
		}

		return pick; // return indx of picked population member
	}


	// perform roulette wheel selection of population member
	unsigned long Population::roulette_wheel(const unsigned long dropped_memb_indx) const
	{
		if(dropped_memb_indx >= m_pMembers.size()) throw Population_exception("Index of dropped member must be within population limits.");

		if(m_pMembers.size() == 1) return 0;
		else if(m_pMembers.size() == 2)
		{
			for (unsigned long i = 0; i < 2; i++) 
			{
				if(i != dropped_memb_indx) return i;
			}
		}

		double total_fitness = 0.0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			total_fitness += m_pMembers[i]->get_fitness();
		}

		total_fitness -= m_pMembers[dropped_memb_indx]->get_fitness();
		
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;

		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(i != dropped_memb_indx)
			{
				offset += m_pMembers[i]->get_fitness();
				if (rand_num <= offset) 
				{
					pick = i;
					break;
				}
			}
		}

		return pick; // return indx of picked population member
	}


	// perform roulette wheel selection of population member
	unsigned long Population::roulette_wheel(const std::set<const unsigned long>& dropped_memb_indices) const
	{
		if(dropped_memb_indices.size() > 0)
		{
			// iterator pointing to the last (the largest) value contained in set
			if(*(--dropped_memb_indices.end()) >= m_pMembers.size()) throw Population_exception("Index of dropped member must be contained in population.");
		}

		if(m_pMembers.size() == 1) return 0;

		double total_fitness = 0.0;
	
		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(dropped_memb_indices.find(i) == dropped_memb_indices.end()) // index NOT contained in set
			{
				total_fitness += m_pMembers[i]->get_fitness();
			}
		}
	
		const double rand_num = random_double(0.0, total_fitness);
		
		double offset = 0.0;
		unsigned long pick = 0;
	
		for (unsigned long i = 0; i < m_pMembers.size(); i++) 
		{
			if(dropped_memb_indices.find(i) == dropped_memb_indices.end()) // if index NOT contained in set
			{
				offset += m_pMembers[i]->get_fitness();
				if (rand_num <= offset) 
				{
					pick = i;
					break;
				}
			}
		}
	
		return pick; // return indx of picked population member
	}
};