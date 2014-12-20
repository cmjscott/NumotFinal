#pragma once

#ifndef _INC_TRANSMISSION
#define _INC_TRANSMISSION

#include <vector>
#include <iostream>

class Transmission
{
public:

	// constructors
	Transmission();
	Transmission(std::vector<double> _gearRatios);
	Transmission(std::vector<double> _gearRatios, std::vector<double> _gearEtas);
	~Transmission();

	//public member functions
	void upshift();
	void downshift();
	double getRatio();
	double getNextRatio();
	double getPreviousRatio();
	bool maxGear;
	bool minGear;

	//public member variables

private:

	//private member functions

	//private member variables
	double shiftTime;
	bool shifting;
	
	int currentGearIndex;
	std::vector<double> gearRatios;
	std::vector<double> gearEtas;
	std::vector<int> shiftLog;
	std::vector<double> rpmLog;
};

#endif