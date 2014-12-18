#pragma once

#ifndef _INC_ENGINE
#define _INC_ENGINE

#include <vector>

class engine
{
public:
	//constructors
	engine();
	engine(std::vector<double> _rpm, std::vector<double> _torque, double _efficiencyFactor = 1);
	~engine();

	//public member functions
	double getTorque(const double* currentRpm);

	//public member variables
	double maxRpm;
	double peakTorqueRpm;
	

private:
	//private member functions
	double findPeakTorqueRpm();
	
	//private member variables
	double efficiencyFactor;
	std::vector<double> rpm;
	std::vector<double> torque;
};

#endif