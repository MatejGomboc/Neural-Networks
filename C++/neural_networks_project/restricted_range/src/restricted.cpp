#include "restricted.h"
#include "restricted_range_exception.h"


namespace restricted_range
{
	template <typename T> 
	void restricted<T>::check_bounds(const T value)
	{
		if(value < m_min) throw Restricted_range_exception("Value smaller than lower bound.");
		if(value > m_max) throw Restricted_range_exception("Value greater than upper bound.");
	}

	template <typename T>
	restricted<T>::restricted(const T value, const T min, const T max)
		:m_min(min), m_max(max) // initialization constructor
	{
		setValue(value);
	}

	template <typename T>
	restricted<T>::restricted(const T min, const T max)
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
	T restricted<T>::operator= (const T value) // overloaded assignment
	{
		setValue(value);

		// return value so we can chain this operator
		return value;
	}

	template <typename T>
	bool restricted<T>::operator< (const T value2) const // overloaded comparisson
	{
		return (m_value < value2);
	}

	template <typename T>
	bool restricted<T>::operator> (const T value2) const // overloaded comparisson
	{
		return (m_value > value2);
	}

	template <typename T>
	T restricted<T>::getValue(void) const
	{
		return m_value;
	}

	template <typename T>
	T restricted<T>::getMin(void) const
	{
		return m_min;
	}

	template <typename T>
	T restricted<T>::getMax(void) const
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


	template class restricted<double>;
}