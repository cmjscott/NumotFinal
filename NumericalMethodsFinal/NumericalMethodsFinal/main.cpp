#include <iostream>
#include <cmath>
#include <conio.h>
#include <vector>
#include <fstream>
#include <iterator>

void outputData(std::vector<std::vector<double> > v);

int main()
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, accel, velocity;






	// Now we'll try to create a 3 by 5 "matrix".
	// First, create a vector with 5 elements
	std::vector<double> v2(5, 99);

	// Now create a vector of 3 elements. 
	// Each element is a copy of v2
	std::vector<std::vector<double> > v2d2(3, v2);

	outputData(v2d2);

	return 0;
}



void outputData(std::vector<std::vector<double> > v)
{

	// open a file in write mode.
	std::ofstream outfile("C://Users//Colton Scott//Documents//output.csv");

	std::cout << "Writing to the file" << std::endl;
	
	// write each line to the output file
	for (int i = 0; i < v.size(); ++i)
	{
		std::copy(v[i].begin(), v[i].end(), std::ostream_iterator<float>(outfile, ","));
		outfile << std::endl;
	}
	outfile << std::endl;

	// close the opened file.
	outfile.close();

	std::cout << "Complete";

	_getch();
}