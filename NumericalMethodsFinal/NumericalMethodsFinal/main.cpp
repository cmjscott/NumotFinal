#include <iostream>
#include <cmath>
#include <conio.h>
#include <vector>
#include <fstream>
#include <iterator>
#include "Vehicle.h"
#include <string>

void outputData(std::vector<std::vector<double> > vec, std::string fileName);
std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double dt);

int main()
{
	std::vector<std::vector<double> > test1Data;
	std::vector<double> time, vel;
	double dt(.01);

	/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
	Cd = .32
	A = 23.4 ft^2 = 2.1739 m^2
	mass = 3715 lbs = 1685.1 kg
	*/
	//Vehicle(double _mass, double _Cdrag, double _fDrive);
	Vehicle Subaru(1685.1, .32, 1000);

	test1Data = simulation1(Subaru, dt);

	outputData(test1Data);

	return 0;
}


std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;

	time.push_back(0);
	vel.push_back(0);

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt));
		time.push_back(time.back() + _dt);
	} while (vel.back() - vel.rbegin()[1] > .0001);

	std::cout << "Your maximum velocity was " << vel.back() << " m/s\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}


void outputData(std::vector<std::vector<double> > vec, std::string fileName)
{

	// open a file in write mode.
	std::ofstream outfile("C://Users//Colton Scott//Documents//output.csv");

	std::cout << "Writing to the file" << std::endl;
	
	// write each line to the output file
	for (int i = 0; i < vec.size(); ++i)
	{
		std::copy(vec[i].begin(), vec[i].end(), std::ostream_iterator<float>(outfile, ","));
		outfile << std::endl;
	}
	outfile << std::endl;

	// close the opened file.
	outfile.close();

	std::cout << "Complete";

	_getch();
}