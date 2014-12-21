#pragma once

#ifndef _INC_ENGINE
#define _INC_ENGINE

#include <vector>
#include <iostream>
#include <string>

class engine
{
public:
	//constructors
	engine();
	engine(std::vector<double> _rpm, std::vector<double> _torque, std::string _name, double _efficiencyFactor = 1);
	~engine();

	//public member functions
	double getTorque(double currentRpm);
	friend std::ostream& operator<< (std::ostream& out, const engine& obj);

	//public member variables
	double maxRpm;
	double peakTorqueRpm;
	std::string name;
	

private:
	//private member functions
	double findPeakTorqueRpm();
	
	//private member variables
	double efficiencyFactor;
	std::vector<double> rpm;
	std::vector<double> torque;
};

#endif