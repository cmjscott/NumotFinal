#include "generators.h"



// prompts user for inputs for all vehicle parameters based on the chosen simulation and returns a vehicle object with the input parameters.

Vehicle generateVehicle(int simulationFlag)
{
	//Variable declarations
	int loopCount;
	double mass, Cdrag, frontArea, diffRatio, wheelRadius, valueHold, maxRpm, driveForce, brakingForce;
	std::vector<double> gearRatios, revMap, torqueMap;
	Vehicle returnVehicle;


	std::cout << std::endl << "--------------------------Enter data for simulation " << simulationFlag << "---------------------------" << std::endl;

	std::cout << std::endl << "Enter mass of Vehicle (kg): ";
	mass = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter Cd: ";
	Cdrag =util::getSanitizedInput<double>();
	
	//Prompts user for a drive force unless simulation 4 was selected
	if (simulationFlag != 4)
	{
		std::cout << std::endl << "Enter drive force (N): ";
		driveForce = util::getSanitizedInput<double>();
	}

	//Vehicle creation is complete if simulation 1 was selected. Returns vehicle.
	
		
	std::cout << std::endl << "Enter front area (m^2): ";
	frontArea = util::getSanitizedInput<double>();

	//Vehicle creation is complete if simulation 2 was selected. Returns vehicle.
	
	
	//Vehicle creation is complete if simulation 3 was selected once a braking force is input. Returns vehicle.
	


	std::cout << std::endl << "Enter wheel radius (m): ";
	wheelRadius = util::getSanitizedInput<double>();

	std::cout << std::endl << "Enter differential ratio: ";
	diffRatio = util::getSanitizedInput<double>();
	
	//Prompts user if they want to use default transmission values
	//Default transmission values are from a 2001 subaru outback H6
	if (util::yesNo("Use default values for transmission?"))
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

		//Prompts user to enter
		for (int i = 0; i < loopCount; ++i)
		{
			std::cout << "Enter gear ratio for gear " << (i + 1) << ": ";

			if (i == 0)
				valueHold = util::getSanitizedInput<double>();
			else
			{
				//This doesn't quite work. It should make sure that the user enters in a smaller gear ratio than the one before it.
				do
					valueHold = util::getSanitizedInput<double>();
				while (valueHold >= gearRatios[i-1]);
			}
			gearRatios[i] = valueHold;
		}
	} //if (util::yesNo("Use default values for transmission?"))

	//Prompts user if they want to use the default torque table
	//Default torque and RPM values are from a 2001 subaru outback H6
	if (util::yesNo("Use default values for torque curve?"))
	{
		revMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
		torqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };

		std::cout << std::endl;
		std::cout << "-Default Torque Table--" << std::endl << std::endl;
		std::cout << " # |  RPM  |  Tq   " << std::endl;
		std::cout << "___________________" << std::endl;
		std::cout << std::left;

		//Prints out the formatted default torque table to the console
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

			//Prompts user for RPM and torque values until the entered RPM excedes the maximum RPM value.
			if (revMap.size() > 0)
			{
				do
					valueHold = util::getSanitizedInput<double>();
				while (valueHold <= revMap.back());
			}
			else
				valueHold = util::getSanitizedInput<double>();

			revMap.push_back(valueHold);

			std::cout << "Torque(" << loopCount << ") = ";
			torqueMap.push_back(util::getSanitizedInput<double>());
			std::cout << std::endl;
			++loopCount;
		} while (revMap.back() < maxRpm);
	}

	std::cout << std::endl << "Created vehicle for simulation " << simulationFlag <<". Press any key to continue" << std::endl << std::endl;
	_getch();

	return Vehicle(mass, Cdrag, frontArea, diffRatio, wheelRadius);
}

Transmission generateTransmission()
{
	int loopCount(0);
	double valueHold(0);
	bool hasEtas;
	std::string transName;
	std::vector<double> gearRatios, gearEtas;

	std::cout << "Enter number of gears: ";
	loopCount = util::getSanitizedInput<int>(1,900);
	gearRatios.resize(loopCount);
	gearEtas.assign(loopCount, 1);

	hasEtas = util::yesNo("Does this gearbox have efficiencies?");

	std::cout << "Enter gearbox name: ";
	transName = util::getSanitizedInput<std::string>();

	//Prompts user to enter values for the transmission
	for (int i = 0; i < loopCount; ++i)
	{
		std::cout << "Enter gear ratio for gear " << (i + 1) << ": ";
		if (i == 0)
		{
			valueHold = util::getSanitizedInput<double>();
		}
		else
		{
			valueHold = util::getSanitizedInput<double>(0, gearRatios[i - 1]);
		}

		gearRatios[i] = valueHold;

		if (hasEtas)
		{
			std::cout << "Enter efficiency for gear " << (i + 1) << ": ";
			valueHold = util::getSanitizedInput<double>(0,1);
			gearEtas[i] = valueHold;
		}
	}

	return Transmission(gearRatios, gearEtas, transName);
}


