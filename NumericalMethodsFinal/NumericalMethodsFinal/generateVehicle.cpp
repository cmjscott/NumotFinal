#include "generateVehicle.h"

int loopCount;
std::string test;
double mass, Cdrag, frontArea, diffRatio, wheelRadius;
std::vector<double> gearRatios, revMap, torqueMap;


Vehicle* generateVehicle()
{
	Vehicle returnVehicle;

	//test = util::getSanitizedInput<std::string>();

	std::cout << "Enter mass of Vehicle (kg): ";
	mass = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter Cd: ";
	Cdrag =util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter front area (m^2): ";
	frontArea = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter wheel radius (m): ";
	wheelRadius = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter differential ratio: ";
	diffRatio = util::getSanitizedInput<double>();
	std::cout << std::endl;

	std::cout << "Enter number of gears: ";
	loopCount = util::getSanitizedInput<int>();
	gearRatios.resize(loopCount);

	for (int i = 0; i < loopCount; ++i)
	{
		std::cout << "Enter gear ratio for gear " << (i + 1) << ": ";
		gearRatios[i] = util::getSanitizedInput<double>();
	}
	

	returnVehicle = Vehicle();
	return &returnVehicle;
}

