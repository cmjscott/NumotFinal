#include "generateVehicle.h"

int loopCount;
std::string test;
double mass, Cdrag, frontArea, diffRatio, wheelRadius, rpmHold, maxRpm, driveForce, brakingForce;
std::vector<double> gearRatios, revMap, torqueMap;

std::vector<double> defaultRevMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
std::vector<double> defaultTorqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };


Vehicle generateVehicle(int simulationFlag)
{
	Vehicle returnVehicle;

	std::cout << "Enter data for simulation " << simulationFlag << " :";

	std::cout << std::endl << "Enter mass of Vehicle (kg): ";
	mass = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter Cd: ";
	Cdrag =util::getSanitizedInput<double>();
	
	if (simulationFlag != 4)
	{
		std::cout << std::endl << "Enter drive force (N): ";
		driveForce = util::getSanitizedInput<double>();
	}

	if (simulationFlag == 1)
		return Vehicle(mass, Cdrag, driveForce);


	std::cout << std::endl << "Enter front area (m^2): ";
	frontArea = util::getSanitizedInput<double>();

	if (simulationFlag == 2)
		return Vehicle(mass, Cdrag, driveForce, frontArea);
	

	if (simulationFlag == 3)
	{
		std::cout << std::endl << "Enter braking force (N): ";
		brakingForce = util::getSanitizedInput<double>();

		return Vehicle(mass, Cdrag, driveForce,frontArea,brakingForce);
	}


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


	std::cout << std::endl << "Enter maximum RPM as an integer: ";
	maxRpm = util::getSanitizedInput<double>();
	
	std::cout << std::endl << "-----Torque table input-----" << std::endl;
	std::cout << "Enter RPM values in ascending order, Torques in N-m" <<std::endl <<std::endl;

	loopCount = 1;

	do
	{
		std::cout << "Entry #: " << loopCount << std::endl;
		std::cout << "RPM(" << loopCount << ") = ";
		if (revMap.size() > 0)
		{
			do
				rpmHold = util::getSanitizedInput<double>();
			while (rpmHold <= revMap.back());
		}
		else 
			rpmHold = util::getSanitizedInput<double>();

		revMap.push_back(rpmHold);

		std::cout << "Torque(" << loopCount << ") = ";
		torqueMap.push_back(util::getSanitizedInput<double>());
		std::cout << std::endl;
		++loopCount;
	} while (revMap.back() < maxRpm);

	std::cout << std::endl << "Created vehicle for simulation " << simulationFlag << std::endl;

	return Vehicle(mass, Cdrag, frontArea, gearRatios, diffRatio, wheelRadius, revMap, torqueMap);
}


