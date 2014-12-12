#include "utilityFunctions.h"


namespace util
{
	bool yesNo(std::string promptText)
	{
		char inputChar;
		std::cout << std::endl << promptText << " (Y/N) : ";
		inputChar = util::getSanitizedInput<char>();

		while (inputChar != 'Y' && inputChar != 'N')
		{
			std::cout << "Try again. Enter 'Y' for yes, and 'N' for no. Inputs are case sensitive.\nEnter 'Y' or 'N' : ";
			inputChar = util::getSanitizedInput<char>();
		}

		if (inputChar == 'Y')
			return true;
		else
			return false;
	}

}
