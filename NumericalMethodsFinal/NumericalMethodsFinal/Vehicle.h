#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

class Vehicle
{
public:
	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _fDrive);
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea);
	Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea, double _fBrake);
	Vehicle(double _mass, double _Cdrag, double _frontalArea,std::vector<double> _gearRatio,
		double _diffRatios, double wheelRadius,std::vector<double> _revMap, std::vector<double> _torqueMap);
	

	//public member functions
	double velocity(double _currVelocity, double dt, double *rho, double throttle = -1);
	double brake(double _currVelocity, double dt, double *rho);
	double engineDriveForce(double throttle);
	double getTorque(double throttle);
	double pubGetRPM();
	~Vehicle();
	
	//public member variables
	int simulationFlag;

private:

	//Member private functions
	double accel(double *rho, double throttle = -1);
	double deccel(double *rho);
	double shift();
	double fDrag(double *rho);    //returns the drag forces ascociated with air resistance
	double Frr();                 //returns the resistance ascociated with rolling
	

	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	double frontArea;
	double fDrive;
	double fBrake;

	std::vector<double> gearRatios;
	std::vector<double> revMap;
	std::vector<double> torqueMap;
	double diffRatio;
	double wheelRadius;
	int currGear;
	static double transEff;

};

