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


	//-------------------------------------Clamp()-----------------------------------------
	// clamps the first argument between the second two
	//-------------------------------------------------------------------------------------
	void clamp(double &arg, const double min, const double max)
	{
		if (arg < min)
		{
			arg = min;
		}

		if (arg > max)
		{
			arg = max;
		}
	}
}
