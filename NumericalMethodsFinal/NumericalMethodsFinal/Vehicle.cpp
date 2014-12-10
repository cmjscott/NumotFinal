#include "Vehicle.h"

/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
Cd = .32
A = 23.4 ft^2 = 2.1739 m^2
mass = 3715 lbs = 1685.1 kg
Gear Ratios: 
1st 2.785 
2nd 1.545 
3rd 1.000 
4th 0.697 
Rev 2.272
Diff 4.11

Tires: 225/60R16 98H SL
wheelRadius = 0.33782 m
*/

double Vehicle::transEff = .7;

Vehicle::Vehicle() {}

//constructor for sim 1
Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	Crr = 30 * Cdrag;
	frontArea = 2; // Used for simulation 1 where the .5 coefficient must be neutralized.
}

//constructor for sim 2
Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	frontArea = _frontalArea;
	Crr = 30 * Cdrag;
}

//constructor for sim 3
Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea, double _fBrake)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	frontArea = _frontalArea;
	fBrake = _fBrake;
	Crr = 30 * Cdrag;
}

//constructor for sim 4
Vehicle::Vehicle(double _mass, double _Cdrag, double _frontalArea, std::vector<double> _gearRatios, double _diffRatio, double _wheelRadius,
	std::vector<double> _revMap, std::vector<double> _torqueMap)
{
	mass = _mass;
	Cdrag = _Cdrag;
	frontArea = _frontalArea;
	Crr = 30 * Cdrag;
	diffRatio = _diffRatio;
	wheelRadius = _wheelRadius;	
	gearRatios = _gearRatios;
	revMap = _revMap;
	torqueMap = _torqueMap;
	currGear = 1;
}


//Honestly not 100% sure what this does.
Vehicle::~Vehicle() {}
 

//Returns the next velocity after dt time has passed, based on current velocity
double Vehicle::velocity(double _currVelocity, double dt, double *rho, double throttle)
{

	double acceleration;
	currVelocity = _currVelocity;
	if (throttle == -1)
		acceleration = accel(rho);
	else
		acceleration = accel(rho, throttle);

	return currVelocity + dt * acceleration;
}

double Vehicle::brake(double _currVelocity, double dt, double *rho)
{
	double acceleration;
	currVelocity = _currVelocity;
	acceleration = deccel(rho);

	return currVelocity + dt * acceleration;
}

//calculates the acceleartion based on the sum of the forces on the car and the mass
double Vehicle::accel(double *rho, double throttle)
{
	double fSum;
	if (throttle == -1)
		fSum = fDrive + fDrag(rho) + Frr();
	else
		fSum = engineDriveForce(throttle) + fDrag(rho) + Frr();

	return fSum / mass;
}


double Vehicle::deccel(double *rho)
{
	double fSum;
	fSum = -fBrake + fDrag(rho) + Frr();
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


// change name and remove fTorque. There is no need for two functions.
// make throttle a member variable and just set it
double Vehicle::engineDriveForce(double throttle)
{
	return getTorque(throttle) * throttle * gearRatios[currGear-1] * diffRatio * transEff / wheelRadius;;
}

double Vehicle::getRPM()
{
	double rpm;
	rpm = pubGetRPM();
	if (rpm > 5000 && currGear < gearRatios.size())
		++currGear;

	return rpm;
}

double Vehicle::pubGetRPM()
{
	double rpm;
	rpm = currVelocity / wheelRadius *(60 / (2 * M_PI)) * gearRatios[currGear-1] * diffRatio;
	if (rpm < 3000 && currGear == 1)
		rpm = 3000;
	if (rpm > 6800)
		rpm = 6800;

	return rpm;
}

double Vehicle::getTorque(double throttle)
{
	double currRPM, currTorque;
	int i = 0;

	currRPM = pubGetRPM();

	do
	{
		++i;
	} while (currRPM < revMap[i]);

	currTorque = torqueMap[i - 1] + (currRPM - revMap[i - 1])*(torqueMap[i] - torqueMap[i - 1]) / (revMap[i] - revMap[i - 1]);

	return currTorque;
}