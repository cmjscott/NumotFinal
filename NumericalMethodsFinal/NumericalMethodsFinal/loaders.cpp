#include "loaders.h"


namespace loaders
{
	std::vector<std::string> loadFile(std::string _fileName)
	{
		std::vector<std::string> data;
		std::ifstream inFile;
		std::string valueHold;

		std::string filePath = getenv("USERPROFILE");
		filePath += "\\Documents\\" + _fileName + ".txt";

		inFile.open(filePath.c_str(), std::ios::in);

		while (!inFile.eof())
		{
			std::getline(inFile, valueHold);
			data.push_back(valueHold);
			valueHold.clear();
		}
		return data;
	}






	Transmission loadTransmission(std::vector<std::string> data)
	{
		Transmission loadedTransmission;
		
		std::string valueHold;
		std::stringstream dataStream;
		
		for (auto i : data)
		{


		}

		return loadedTransmission;
	}

}