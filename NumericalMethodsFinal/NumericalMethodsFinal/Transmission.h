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
	void dounshift();

	//public member variables

private:

	//private member variables
	double currentGear;
	double shiftTime;
	std::vector<double> gearRatios;
	std::vector<double> gearEtas;
	
};

#endif