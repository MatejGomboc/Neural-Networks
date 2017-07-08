#pragma once

#include <exception>
#include <string>


namespace Neural_networks
{
	class Neural_network_exception: public std::exception
	{
	private:
		std::string m_sMessage;
	public:
		explicit Neural_network_exception(const std::string message);
		virtual const char* what() const throw();
	};
};