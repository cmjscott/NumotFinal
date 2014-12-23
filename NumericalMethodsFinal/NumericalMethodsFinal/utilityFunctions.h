#pragma once

#ifndef _INC_UTILITYFUNCTIONS
#define _INC_UTILITYFUNCTIONS

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <climits>

// for some reason including this fucks up some stuff.
//#include <Windows.h>



namespace util
{
	bool yesNo(std::string promptText);

	//outputs a data matrix to the user's documents folder as a .dat file with the given filename
	template<typename T, typename A>
	void outputData(std::vector<std::vector<T, A> > const& vec, std::string _fileName)
	{
		std::ofstream outfile;
		std::string filePath = getenv("USERPROFILE");
		filePath += "\\Documents\\" + _fileName + ".csv";

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


	//gets input from cin and will loop until the input is of the specified type, rejecting invalid inputs.
	template <typename T>
	T getSanitizedInput()
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			if (std::cin.fail())
				std::cin.clear();

			std::cin.ignore(255, '\n');			// clear out any additional input from the stream until the end of the line

			if (std::cin.gcount() > 1)								// if the ignore cleared out more than one character, assume that bad data was passed to the input stream
			{
				std::cout << "Error: invalid data entered." << std::endl;
				std::cout << "Re-enter value as (" << typeid(T).name() << "): ";
			}
			else
				failedInput = false;

		} while (failedInput);

		return terminalInput;
	}


	template <typename T>
	T getSanitizedInput(double lBound, double uBound)
	{
		T terminalInput;
		bool failedInput = true;

		do
		{
			std::cin >> terminalInput;

			
			if (std::cin.fail())
				std::cin.clear();
			
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	

			if (std::cin.gcount() > 1)
			{
				std::cout << "Error: invalid data entered." << std::endl;
				std::cout << "Re-enter value as (" << typeid(T).name() << ")";
				std::cout << " between ( " << lBound << " , " << uBound << " ): ";
			}
			else
			{
				if (terminalInput <= uBound && terminalInput >= lBound)
					failedInput = false;
				else
				{
					std::cout << "Error: data entered outside of given bounds." << std::endl;
					std::cout << "Re-enter a value between ( " << lBound << " , " << uBound << " ): ";
				}
			}
		} while (failedInput);

		return terminalInput;
	}


	//make another getSanitizedInput function that takes two parameter types, one being the type of data you want back and the other being the stream object
	template <typename T>
	T getSanitizedInput(T in)
	{
		T extractedValue;
		bool failedInput = true;

		do
		{
			in >> extractedValue;

			if (in.fail())
			{
				in.clear();
				failedInput = false;
			}
				

				

		} while (failedInput);

		return terminalInput;
	}
} // namespace util

#endif