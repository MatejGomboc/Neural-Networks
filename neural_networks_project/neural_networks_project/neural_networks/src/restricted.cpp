#include "restricted.h"


namespace neural_networks
{
	template <typename T, int min, int max> 
	void restricted<T, min, max>::check_bounds (const T& value)
	{
		if(value < min) throw "Value smaller than lower bound.";
		if(value > max) throw "Value greater than upper bound.";
	}

	template <typename T, int min, int max>
	restricted<T, min, max>::restricted(T value) // initialization constructor
	{
		check_bounds(value);
		m_value = value;
	}

	template <typename T, int min, int max>
	restricted<T, min, max>::operator T() // overloaded typecast to type T
	{ 
		return m_value;
	}

	template <typename T, int min, int max>
	restricted<T, min, max>& restricted<T, min, max>::operator= (const T& value) // overloaded assignment
	{
		check_bounds(value);

		// do the copy
		m_value = value;

		// return the existing object so we can chain this operator
		return *this;
	}

	template <typename T, int min, int max>
	bool operator< (const restricted<T, min, max>& value1, const T& value2) // overloaded comparisson
	{
		return ((value1.m_value < value2) ? true : false);
	}

	template <typename T, int min, int max>
	bool operator> (const restricted<T, min, max>& value1, const T& value2) // overloaded comparisson
	{
		return ((value1.m_value > value2) ? true : false);
	}

	template class restricted<double, 0, 1>;
	template class restricted<double, -1000, 1000>;
}