#include "utils.h"
#include <sstream>
#include <string>


namespace Utils
{
	//--------------------------itos------------------------------------
	// converts an integer to a string
	//------------------------------------------------------------------		
	std::wstring itos(const int arg)
	{
		std::ostringstream buffer;

		//send the int to the ostringstream
		buffer << arg;	

		//capture the string
		return string_to_wstring(buffer.str());		
	}


	//--------------------------ftos------------------------------------
	// converts a float to a string
	//------------------------------------------------------------------		
	std::wstring ftos (const float arg)
	{
		std::ostringstream buffer;

		//send the int to the ostringstream
		buffer << arg;	

		//capture the string
		return string_to_wstring(buffer.str());		
	}


	//--------------------------string_to_wstring-----------------------
	// converts a std::string to std::wstring
	//------------------------------------------------------------------
	std::wstring string_to_wstring(const std::string arg)
	{
		return std::wstring(arg.begin(), arg.end());
	}
}
