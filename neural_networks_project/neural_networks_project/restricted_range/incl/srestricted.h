#pragma once


namespace restricted_range
{
	template <typename T, int m_min, int m_max>
	class srestricted
	{
	private:
		T m_value;

	private:
		void check_bounds(const T value);

	public:
		explicit srestricted(const T value); // initialization constructor
		explicit srestricted(void); // initialization constructor
		
		operator T() const; // overloaded typecast
		T operator= (const T value); // oveloaded assignment
		
		bool operator< (const T value2) const; // oveloaded comparisson
		bool operator> (const T value2) const; // oveloaded comparisson
		
		T getValue(void) const;
		void setValue(const T value);

		T getMin(void) const;
		T getMax(void) const;
	};
}