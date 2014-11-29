#include <iostream> //for cin/cout
#include <cmath>
#include <conio.h> // for _getch()
#include <vector>
#include <fstream>
#include <iterator>
#include "Vehicle.h"
#include <string>

//function prototypes
void outputData(std::vector<std::vector<double> > vec, std::string fileName);
std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double dt, double _rho);


int main()
{
	std::vector<std::vector<double> > test1Data, test2Data;
	std::vector<double> time, vel;
	const double staticRho(1);
	double rho(1.2041);
	double dt(.001);


	/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
	Cd = .32
	A = 23.4 ft^2 = 2.1739 m^2
	mass = 3715 lbs = 1685.1 kg
	Drive force ~ 1500 N
	*/

	//create vehicle objects for the simulation
	Vehicle SubaruSim1(1685.1, .32, 1500);
	Vehicle SubaruSim2(1685.1, .32, 1500, 2.1739);

	//Run simulations
	test1Data = simulation1(SubaruSim1, dt, staticRho);
	test2Data = simulation1(SubaruSim2, dt, rho);


	//Output data for matlab
	outputData(test1Data, "sim1");
	outputData(test2Data, "sim2");

	std::cout << "Simulations complete, press any key to quit";
	_getch();
	return 0;
}


std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt, double _rho)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	

	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &_rho));
		time.push_back(time.back() + _dt);
	} while ((vel.back() - vel.rbegin()[1])/_dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	std::cout << "Your maximum velocity was " << vel.back() << " m/s\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl << std::endl;

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
	std::cout << "Sucsess writing data to:" << std::endl <<  filePath << std::endl <<std::endl;
}