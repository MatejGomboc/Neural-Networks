#include "IRestrictedAccessor.h"
#include "restricted.h"


namespace neural_networks
{
	template <typename T>
	void IRestrictedAccessor<T>::setMin(const T min, restricted<T>& value)
	{
		value.m_min = min;
	}

	template <typename T>
	void IRestrictedAccessor<T>::setMax(const T max, restricted<T>& value)
	{
		value.m_max = max;
	}

	template class IRestrictedAccessor<double>;
};