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
	frontArea = 2; //
}


Vehicle::~Vehicle()
{

}
 


double Vehicle::velocity(double _currVelocity, double dt, double *rho)
{
	double acceleration;
	currVelocity = _currVelocity;
	acceleration = accel(rho);

	return currVelocity + dt * acceleration;
}

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