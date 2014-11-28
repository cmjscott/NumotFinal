#pragma once

#ifndef VEHICLE_H_
#define VEHICLE_H_


/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
Cd = .32
A = 23.4 ft^2 = 2.1739 m^2
mass = 3715 lbs = 1685.1 kg
*/


class Vehicle
{
public:

	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag, double _fDrive);
	//Vehicle(double _mass, double _Cdrag, double _A);
	//Vehicle(double _mass, double _Cdrag, double _A, double _gearRatio, double _diffRatio, double _wheelRadius);

	//member functions
	double velocity(double _currVelocity, double dt, double *rho);
	
	~Vehicle();

	//Member public properties
	double fDrive;

private:

	//Member private functions
	double accel(double *rho);
	double fDrag(double *rho);
	double Frr();

	//Member private properties
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	double frontArea;

	/* to be added later
	
	double gearRatio;
	double diffRatio;
	double wheelRadius;
	double torque;
	static const double transEff;
	*/
};

//const double transEff = 0.7;


#endif // VEHICLE_H_