#pragma once

namespace neural_networks
{
	template <typename T, int min, int max>
	class restricted
	{
	private:
		T m_value;
	private:
		void check_bounds (const T& value);
	public:
		restricted(T value); // initialization constructor
		operator T(); // overloaded typecast
		restricted<T, min, max>& operator= (const T& value); // oveloaded assignment
		friend bool operator< (const restricted<T, min, max>& value1, const T& value2); // oveloaded comparisson
		friend bool operator> (const restricted<T, min, max>& value1, const T& value2); // oveloaded comparisson
	};
}