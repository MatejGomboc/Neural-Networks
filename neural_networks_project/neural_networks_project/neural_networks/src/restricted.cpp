#include "restricted.h"


namespace neural_networks
{
	template <typename T> 
	void restricted<T>::check_bounds (const T& value)
	{
		if(value < m_min) throw "Value smaller than lower bound.";
		if(value > m_max) throw "Value greater than upper bound.";
	}

	template <typename T>
	restricted<T>::restricted(const T value, const  T& min, const  T& max)
		:m_min(min), m_max(max) // initialization constructor
	{
		setValue(value);
	}

	template <typename T>
	restricted<T>::restricted(const T& min, const T& max)
		:m_min(min), m_max(max) // initialization constructor
	{
		m_value = m_min;
	}

	template <typename T>
	restricted<T>::operator T() const // overloaded typecast to type T
	{ 
		return getValue();
	}

	template <typename T>
	restricted<T>& restricted<T>::operator= (const T& value) // overloaded assignment
	{
		setValue(value);

		// return the existing object so we can chain this operator
		return *this;
	}

	template <typename T>
	bool restricted<T>::operator< (const T& value2) const // overloaded comparisson
	{
		return (m_value < value2);
	}

	template <typename T>
	bool restricted<T>::operator> (const T& value2) const // overloaded comparisson
	{
		return (m_value > value2);
	}

	template <typename T>
	bool operator< (const T& value2, restricted<T>& value1) // overloaded comparisson
	{
		return (value1 > value2);
	}

	template <typename T>
	bool operator> (const T& value2, restricted<T>& value1) // overloaded comparisson
	{
		return (value1 < value2);
	}

	template <typename T>
	const T& restricted<T>::getValue(void) const
	{
		return m_value;
	}

	template <typename T>
	const T& restricted<T>::getMin(void) const
	{
		return m_min;
	}

	template <typename T>
	const T& restricted<T>::getMax(void) const
	{
		return m_max;
	}

	template <typename T>
	void restricted<T>::setValue(const T value)
	{
		check_bounds(value);

		// do the copy
		m_value = value;
	}

	template <typename T>
	void restricted<T>::setMin(const T min)
	{
		m_min = min;
	}

	template <typename T>
	void restricted<T>::setMax(const T max)
	{
		m_max = max;
	}



	template class restricted<double>;
}