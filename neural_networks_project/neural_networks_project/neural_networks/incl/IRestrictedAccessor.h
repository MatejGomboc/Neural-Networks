#pragma once

#include "restricted.h"
#include "IRestrictedRange.h"


namespace neural_networks
{
	template <typename T>
	class IRestrictedAccessor
	{
	private:
		IRestrictedAccessor<T>();
	public:
		static void setMin(const T min, restricted<T>& value);
		static void setMax(const T max, restricted<T>& value);
		friend class IRestrictedRange<T>;
	};
};