#pragma once

namespace neural_networks
{
	template <typename T>
	class restricted
	{
	public:
		T m_min;
		T m_max;
	private:
		T m_value;
	private:
		void check_bounds (const T& value);
	public:
		explicit restricted(const T value, const T& min, const T& max); // initialization constructor
		explicit restricted(const T& min, const T& max); // initialization constructor
		operator T() const; // overloaded typecast
		restricted<T>& operator= (const T& value); // oveloaded assignment
		bool operator< (const T& value2) const; // oveloaded comparisson
		bool operator> (const T& value2) const; // oveloaded comparisson
		const T& getValue(void) const;
		void setValue(const T value);
	};

	template <typename T>
	extern bool operator< (const T& value2, restricted<T>& value1); // overloaded comparisson

	template <typename T>
	extern bool operator> (const T& value2, restricted<T>& value1); // overloaded comparisson
}