#include "srestricted.h"
#include "restricted_range_exception.h"


namespace restricted_range
{
	template <typename T, int m_min, int m_max>
	void srestricted<T, m_min, m_max>::check_bounds(const T value)
	{
		if(value < m_min) throw Restricted_range_exception("Value smaller than lower bound.");
		if(value > m_max) throw Restricted_range_exception("Value greater than upper bound.");
	}

	template <typename T, int m_min, int m_max>
	srestricted<T, m_min, m_max>::srestricted(const T value) // initialization constructor
	{
		setValue(value);
	}

	template <typename T, int m_min, int m_max>
	srestricted<T, m_min, m_max>::srestricted(void) // initialization constructor
	{
		m_value = m_min;
	}

	template <typename T, int m_min, int m_max>
	srestricted<T, m_min, m_max>::operator T() const // overloaded typecast to type T
	{ 
		return getValue();
	}

	template <typename T, int m_min, int m_max>
	T srestricted<T, m_min, m_max>::operator= (const T value) // overloaded assignment
	{
		setValue(value);

		// return value so we can chain this operator
		return value;
	}

	template <typename T, int m_min, int m_max>
	bool srestricted<T, m_min, m_max>::operator< (const T value2) const // overloaded comparisson
	{
		return (m_value < value2);
	}

	template <typename T, int m_min, int m_max>
	bool srestricted<T, m_min, m_max>::operator> (const T value2) const // overloaded comparisson
	{
		return (m_value > value2);
	}

	template <typename T, int m_min, int m_max>
	T srestricted<T, m_min, m_max>::getValue(void) const
	{
		return m_value;
	}

	template <typename T, int m_min, int m_max>
	T srestricted<T, m_min, m_max>::getMin(void) const
	{
		return m_min;
	}

	template <typename T, int m_min, int m_max>
	T srestricted<T, m_min, m_max>::getMax(void) const
	{
		return m_max;
	}

	template <typename T, int m_min, int m_max>
	void srestricted<T, m_min, m_max>::setValue(const T value)
	{
		check_bounds(value);

		// do the copy
		m_value = value;
	}


	template class srestricted<double, 0, 1>;
	template class srestricted<double, -1000, 1000>;
}