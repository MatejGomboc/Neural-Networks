#include "restricted_range_exception.h"
#include <string>


namespace restricted_range
{
	Restricted_range_exception::Restricted_range_exception(const std::string message)
		: m_sMessage(message)
	{
	}

	const char* Restricted_range_exception::what() const throw()
	{
        return m_sMessage.c_str();
    }
};