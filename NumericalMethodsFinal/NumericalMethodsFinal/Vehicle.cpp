#include "Vehicle.h"

/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
Cd = .32
A = 23.4 ft^2 = 2.1739 m^2
mass = 3715 lbs = 1685.1 kg
*/

Vehicle::Vehicle() {}



Vehicle::Vehicle(double _mass, double _Cdrag)
{
	mass = _mass;
	Cdrag = _Cdrag;
	Crr = 30 * Cdrag;

}


Vehicle::~Vehicle()
{

}
 


double Vehicle::velocity(double _currVelocity, double dt)
{
	double acceleration;
	currVelocity = _currVelocity;


}

double accel()
{

}

double fDrag()
{

}

double Frr()
{

}