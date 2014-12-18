#include "utilityFunctions.h"


namespace util
{
	//simple yes/no boolean with prompt and input
	bool yesNo(std::string promptText)
	{
		char inputChar;
		std::cout << std::endl << promptText << " (Y/N) : ";
		inputChar = util::getSanitizedInput<char>();

		while ((inputChar != 'Y' && inputChar != 'N' && inputChar != 'y' && inputChar != 'n'))
		{
			std::cout << "Try again. Enter 'Y' for yes, and 'N' for no.\nEnter 'Y' or 'N' : ";
			inputChar = util::getSanitizedInput<char>();
		}

		if (inputChar == 'Y' || inputChar == 'y')
			return true;
		else
			return false;
	}

	/*
	for adding a << operator to vector for later

	std::vector<std::string>& operator<<(std::vector<std::string>& op, std::string str) 
	{
		op.push_back(str);
		return op;
	}*/
}