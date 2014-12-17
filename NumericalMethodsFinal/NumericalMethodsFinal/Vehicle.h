#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
//#include "prettyprint.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Vehicle
{
public:
	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _fDrive);															//constructor for simulation 1
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea);										//constructor for simulation 2
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea, double _fBrake);						//constructor for simulation 3
	Vehicle(double _mass, double _Cdrag, double _frontalArea,std::vector<double> _gearRatio,						// constructor for simulation 4
		double _diffRatios, double wheelRadius,std::vector<double> _revMap, std::vector<double> _torqueMap, double _rho = 1);
	

	//public member functions
	double velocity(double _currVelocity, double dt, double throttle = -1);
	double brake(double _currVelocity, double dt);
	double engineDriveForce(double throttle);
	double getTorque(double throttle);
	double getRPM();
	void setRho(double _rho);
	~Vehicle();

	//public friend functions
	friend std::ostream& operator << (std::ostream& out, const Vehicle& obj);
	
	//public member variables
	int simulationFlag;

private:

	//Member private functions
	double accel(double throttle = -1);
	double deccel();
	void shift();				  //shifts if rpm range is ideal
	double fDrag();    //returns the drag forces ascociated with air resistance
	double Frr();                 //returns the resistance ascociated with rolling
	int findPeakTorque();
	
	

	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	double frontArea;
	double fDrive;
	double fBrake;
	double rho;

	std::vector<double> gearRatios;
	std::vector<double> revMap;
	std::vector<double> torqueMap;
	double diffRatio;
	double wheelRadius;
	int currGear;
	int peakTorqueIndex;
	static double transEff;
};

