#pragma once


namespace restricted_range
{
	template <typename T>
	class restricted;

	template <typename T>
	extern void restricted_setMin(T min, restricted<T>& value);

	template <typename T>
	extern void restricted_setMax(T max, restricted<T>& value);

	template <typename T>
	class restricted
	{
	private:
		T m_min;
		T m_max;
		T m_value;

	private:
		void check_bounds(const T value);
		friend void restricted_setMin <>(T min, restricted<T>& value);
		friend void restricted_setMax <>(T max, restricted<T>& value);
	public:
		explicit restricted(const T value, const T min, const T max); // initialization constructor
		explicit restricted(const T min, const T max); // initialization constructor
		
		operator T() const; // overloaded typecast
		T operator= (const T value); // oveloaded assignment
		
		bool operator< (const T value2) const; // oveloaded comparisson
		bool operator> (const T value2) const; // oveloaded comparisson
		
		T getValue(void) const;
		void setValue(const T value);

		T getMin(void) const;
		T getMax(void) const;
	};

	template <typename T>
	void restricted_setMin(T min, restricted<T>& value)
	{
		value.m_min = min;
	}

	template <typename T>
	void restricted_setMax(T max, restricted<T>& value)
	{
		value.m_max = max;
	}
}