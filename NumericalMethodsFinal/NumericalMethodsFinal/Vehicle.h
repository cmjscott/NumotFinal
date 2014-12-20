#pragma once

#ifndef _INC_VEHICLE
#define _INC_VEHICLE

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
//#include "prettyprint.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "engine.h"
#include "Transmission.h"

class Vehicle
{
public:
	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _frontalArea,													//constructor for simulation 4
		double _diffRatios, double wheelRadius, double _rho = 1);
	

	//public member functions
	std::vector<double> simulateNextTimestep(double _currVelocity, double _dt, double _throttle = -1);
	void setRho(double _rho);
	void attachEngine(engine* _engine);
	void attachTransmission(Transmission* _transmission);
	~Vehicle();

	//public friend functions
	friend std::ostream& operator << (std::ostream& out, const Vehicle& obj);
	
	//public member variables
	int simulationFlag;

private:

	//Member private functions
	double accel();
	double deccel();
	void shift();				  //shifts if rpm range is ideal
	double fDrag();    //returns the drag forces ascociated with air resistance
	double Frr();                 //returns the resistance ascociated with rolling
	double velocity();
	double brake();
	double engineDriveForce();
	double getRPM();

	//depreciated
	//int findPeakTorque();
	

	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double frontArea;
	double fDrive;
	double fBrake;
	double rho;
	double diffRatio;
	double wheelRadius;
	double currentThrottle;
	double dt;
	double transEff;
	double currVelocity;

	double velocityHolder;
	double accelerationHolder;
	double torqueHolder;
	double rpmHolder;

	std::vector<double> stateData;

	engine* attachedEngine;
	Transmission* attachedTransmission;

	//depreciated
	//std::vector<double> revMap;
	//std::vector<double> torqueMap;
	//int peakTorqueIndex;
};

#endif
