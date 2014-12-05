#include "utilityFunctions.h"


namespace util
{
	void util::outputData(std::vector<std::vector<double> > vec, std::string _fileName)
	{
		std::ofstream outfile;
		std::string filePath = "C://Users//cms6420//Documents//" + _fileName + ".dat";

		// open file in write mode, overwriting if file exists.
		//Note: this could lead to loss of data and should be dealt with.
		outfile.open(filePath.c_str(), std::ios::out | std::ios::trunc);

		//just a double check if the file is open or not.
		//TODO: write in error handling if file doesnt open or isnt open.
		if (outfile.is_open())
		{
			std::cout << "Writing to the file" << std::endl;

			// write each line to the output file as column vectors
			for (int i = 0; i < vec[0].size(); ++i)
			{
				for (int j = 0; j < vec.size(); ++j)
				{
					outfile << vec[j][i] << ',';
				}
				outfile << std::endl;
			}
			outfile << std::endl;

			// close the opened file.
			outfile.close();
		}//if (outfile.is_open())

		//sucsess message
		std::cout << "Sucsess writing data to:" << std::endl << filePath << std::endl << std::endl;
	}
}
