#include "Vehicle.h"
#include <cmath>
#include <iostream>

/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
Cd = .32
A = 23.4 ft^2 = 2.1739 m^2
mass = 3715 lbs = 1685.1 kg
*/

Vehicle::Vehicle() {}


Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	Crr = 30 * Cdrag;
	frontArea = 2; // Used for simulation 1 where the .5 coefficient must be neutralized.
}

Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	frontArea = _frontalArea;
	Crr = 30 * Cdrag;
	
}

//Honestly not 100% sure what this does.
Vehicle::~Vehicle()
{
}
 

//Returns the next velocity after dt time has passed, based on current velocity
double Vehicle::velocity(double _currVelocity, double dt, double *rho)
{

	double acceleration;
	currVelocity = _currVelocity;
	acceleration = accel(rho);

	return currVelocity + dt * acceleration;
}

//calculates the acceleartion based on the sum of the forces on the car and the mass
double Vehicle::accel(double *rho)
{
	double fSum;
	fSum = fDrive + fDrag(rho) + Frr();
	return fSum / mass;
}

double Vehicle::fDrag(double *rho)
{
	return -0.5 * Cdrag * frontArea * (*rho) * std::pow(currVelocity, 2);
}

double Vehicle::Frr()
{
	return -Crr * currVelocity;
}