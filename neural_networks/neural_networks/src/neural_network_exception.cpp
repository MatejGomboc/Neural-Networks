#include "neural_network_exception.h"
#include <string>


namespace Neural_networks
{
	Neural_network_exception::Neural_network_exception(const std::string message)
		: m_sMessage(message)
	{
	}

	const char* Neural_network_exception::what() const throw()
	{
        return m_sMessage.c_str();
    }
};