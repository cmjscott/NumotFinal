#pragma once

#ifndef _INC_TRANSMISSION
#define _INC_TRANSMISSION

#include <vector>
#include <iostream>
#include <string>

class Transmission
{
public:

	// constructors
	Transmission();
	Transmission(std::vector<double> _gearRatios, std::string _name);
	Transmission(std::vector<double> _gearRatios, std::vector<double> _gearEtas, std::string _name);
	~Transmission();

	//public member functions
	void upshift();
	void downshift();
	double getRatio();
	double getNextRatio();
	double getPreviousRatio();
	bool maxGear;
	bool minGear;
	friend std::ostream& operator<< (std::ostream& out, const Transmission& obj);

	//public member variables
	std::string name;

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