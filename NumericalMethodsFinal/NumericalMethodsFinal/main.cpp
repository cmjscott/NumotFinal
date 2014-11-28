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
	std::vector<std::vector<double> > test1Data, test2Data;
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

	dt = .001;

	test2Data = simulation1(Subaru, dt);

	outputData(test1Data, "test1pointerTest");
	outputData(test2Data, "test2pointerTest");

	_getch();
	return 0;
}


std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double rho(1);

	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);


	//NOTE: Need to tweak termination conditions. If I reduce dt, it is terminating too quickly.
	// maybe base termination on acceleration instead of delta velocity?
	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &rho));
		time.push_back(time.back() + _dt);
	} while ((vel.back() - vel.rbegin()[1])/_dt > .0001);

	std::cout << "Your maximum velocity was " << vel.back() << " m/s\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}


void outputData(std::vector<std::vector<double> > vec, std::string _fileName)
{
	std::ofstream outfile;
	std::string filePath = "C://Users//Colton Scott//Documents//" + _fileName + ".dat";
	
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
	std::cout << "Sucsess writing data to:" << std::endl <<  filePath << std::endl;
}