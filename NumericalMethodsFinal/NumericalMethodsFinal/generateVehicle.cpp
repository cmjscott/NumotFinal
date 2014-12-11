#include "generateVehicle.h"

int loopCount;
char yesNo;
double mass, Cdrag, frontArea, diffRatio, wheelRadius, rpmHold, maxRpm, driveForce, brakingForce;
std::vector<double> gearRatios, revMap, torqueMap;




Vehicle generateVehicle(int simulationFlag)
{
	Vehicle returnVehicle;


	std::cout << std::endl << "--------------------------Enter data for simulation " << simulationFlag << "---------------------------" << std::endl;

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

	
	std::cout << std::endl << "Use default values for transmission? (Y/N) : ";
	yesNo = util::getSanitizedInput<char>();

	while (yesNo != 'Y' && yesNo != 'N')
	{
		std::cout << "Try again. Enter 'Y' for yes, and 'N' for no. Inputs are case sensitive.\nEnter 'Y' or 'N' : ";
		yesNo = util::getSanitizedInput<char>();
	}

	if (yesNo == 'Y')
	{
		gearRatios = { 2.785, 1.545, 1, .697 };

		std::cout << std::endl;
		std::cout << "--Default Gear Ratios--" << std::endl << std::endl;
		std::cout << " Gear | Ratio" << std::endl;
		std::cout << "_____________" << std::endl;

		for (int i = 0; i < gearRatios.size(); ++i)
		{
			std::cout << std::setprecision(4);
			switch (i)
			{
			case 0:
				std::cout << " 1st  | " << gearRatios[i] << std::endl;
				break;
			case 1:
				std::cout << " 2nd  | " << gearRatios[i] << std::endl;
				break;
			case 2:
				std::cout << " 3rd  | " << gearRatios[i] << std::endl;
				break;
			default:
				std::cout << " " << i+1 <<  "th  | " << gearRatios[i] << std::endl;
				break;
			}
		}
	}
	else
	{
		std::cout << "Enter number of gears: ";
		loopCount = util::getSanitizedInput<int>();
		gearRatios.resize(loopCount);

		for (int i = 0; i < loopCount; ++i)
		{
			std::cout << "Enter gear ratio for gear " << (i + 1) << ": ";
			gearRatios[i] = util::getSanitizedInput<double>();
		}
	}
	
	std::cout << std::endl << "Use default values for torque curve? (Y/N) : ";
	yesNo = util::getSanitizedInput<char>();

	while (yesNo != 'Y' && yesNo != 'N')
	{
		std::cout << "Try again. Enter 'Y' for yes, and 'N' for no. Inputs are case sensitive.\nEnter 'Y' or 'N' : ";
		yesNo = util::getSanitizedInput<char>();
	}

	if (yesNo == 'Y')
	{
		revMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
		torqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };

		std::cout << std::endl;
		std::cout << "-Default Torque Table--" << std::endl << std::endl;
		std::cout << " # |  RPM  |  Tq   " << std::endl;
		std::cout << "___________________" << std::endl;
		std::cout << std::left;

		for (int i = 0; i < revMap.size(); ++i)
		{
			std::cout << std::setw(3) << i + 1 << "|  " << std::setw(5) << revMap[i] << "|  " << std::setw(5) << torqueMap[i] << std::endl;
		}
		std::cout << "___________________" << std::endl << std::endl;
	}
	else
	{
		std::cout << std::endl << "Enter maximum RPM as an integer: ";
		maxRpm = util::getSanitizedInput<double>();

		std::cout << std::endl << "-----Torque table input-----" << std::endl;
		std::cout << "Enter RPM values in ascending order, Torques in N-m" << std::endl << std::endl;

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
	}

	std::cout << std::endl << "Created vehicle for simulation " << simulationFlag <<". Press any key to continue" << std::endl << std::endl;
	_getch();

	return Vehicle(mass, Cdrag, frontArea, gearRatios, diffRatio, wheelRadius, revMap, torqueMap);
}




