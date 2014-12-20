#pragma once

#ifndef _INC_TRANSMISSION
#define _INC_TRANSMISSION

#include <vector>

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

	//public member variables

private:

	//private member functions

	//private member variables
	double shiftTime;
	bool shifting;
	int currentGearIndex;
	std::vector<double> gearRatios;
	std::vector<double> gearEtas;
	
};

#endif