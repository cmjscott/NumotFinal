#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>



typedef enum {
	UNSIGNED,
	SIGNED, 
	NON_NUMERIC
} signedFlag_e;


namespace util
{
	bool yesNo(std::string promptText);

	template<typename T, typename A>
	void outputData(std::vector<std::vector<T, A> > const& vec, std::string _fileName)
	{
		std::ofstream outfile;
		std::string filePath = getenv("USERPROFILE");
		filePath += "\\Documents\\" + _fileName + ".dat";

		// open file in write mode, overwriting if file exists.
		//Note: this could lead to loss of data and should be dealt with.
		outfile.open(filePath.c_str(), std::ios::out | std::ios::trunc);

		if (outfile.is_open())
		{
			std::cout << "Writing to file:" << std::endl;

			// write each line to the output file as column vectors
			// this is clunky, since it assumes that no vector has fewer elements than the first
			for (int i = 0; i < vec[0].size(); ++i)
			{
				for (int j = 0; j < vec.size(); ++j)
				{
					outfile << vec[j][i];
					if (j < vec.size() - 1)
						outfile << ',';
				}
				outfile << std::endl;
			}
			outfile << std::endl;
			outfile.close();
		}//if (outfile.is_open())

		std::cout << "Sucsess writing data to:" << std::endl << filePath << std::endl << std::endl;
	}

	template <typename T>
	T getSanitizedInput(double lBound = LONG_MIN, double uBound = LONG_MAX,  signedFlag_e _signFlag = NON_NUMERIC)
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			//checks if the stream encountered a fatal error (ie. a char was entered)
			if (std::cin.fail())
			{
				std::cin.clear(); // clears the error
			}

			// clear out any additional input from the stream until the end of the line
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			// if the ignore cleared out more than one character (the null terminator)
			// assume that bad data was passed to the input stream
			// because otherwise the stream would be clear, since all the data was placed into inputInt
			if (std::cin.gcount() > 1)
			{
				std::cout << "Error: invalid data entered." << std::endl << "Re-enter value as (" << typeid(T).name() << "): ";
			}
			else 
			{
				switch (_signFlag)
				{
				case UNSIGNED:

					break;
				case SIGNED:

					break;
				default:
					break;
				}


				failedInput = false;
			}
		} while (failedInput);

		

		return terminalInput;
	}
}
