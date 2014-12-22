#pragma once

#ifndef _INC_SAVERS
#define _INC_SAVERS

#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

namespace savers
{
	template<typename T>
	void saveComponent(T const& obj, std::string _fileName)
	{
		
		std::string filePath = getenv("USERPROFILE");
		filePath += "\\Documents\\" + _fileName + ".txt";
		std::ofstream outfile;

		// open file in write mode, overwriting if file exists.
		//Note: this could lead to loss of data and should be dealt with.
		outfile.open(filePath.c_str(), std::ios::out | std::ios::trunc);

		if (outfile.is_open())
		{
			std::cout << "Writing to file:" << std::endl;
			outfile << obj;
			outfile.close();
		}//if (outfile.is_open())

		std::cout << "Sucsess writing data to:" << std::endl << filePath << std::endl << std::endl;
	}
}

#endif