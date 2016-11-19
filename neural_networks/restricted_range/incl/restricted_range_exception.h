#pragma once

#include <exception>
#include <string>


namespace Restricted_range
{
	class Restricted_range_exception: public std::exception
	{
	private:
		std::string m_sMessage;
	public:
		explicit Restricted_range_exception(const std::string message);
		virtual const char* what() const throw();
	};
};
