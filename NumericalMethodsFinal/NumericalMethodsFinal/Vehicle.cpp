#include "Vehicle.h"
#include <cmath>

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
}


Vehicle::~Vehicle()
{

}
 


double Vehicle::velocity(double _currVelocity, double dt)
{
	double acceleration;
	currVelocity = _currVelocity;
	acceleration = accel();

	return currVelocity + dt * acceleration;
}

double Vehicle::accel()
{
	double fSum;
	fSum = fDrive + fDrag() + Frr();
	return fSum / mass;
}

double Vehicle::fDrag()
{
	return -Cdrag * std::pow(currVelocity, 2);
}

double Vehicle::Frr()
{
	return -Crr * currVelocity;
}