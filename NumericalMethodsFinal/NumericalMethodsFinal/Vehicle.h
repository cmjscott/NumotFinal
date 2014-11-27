#pragma once

#ifndef VEHICLE_H_
#define VEHICLE_H_


class Vehicle
{
public:

	// Constructors
	Vehicle();
	Vehicle(double _mass, double _Cdrag);
	//Vehicle(double _mass, double _Cdrag, double _A);
	//Vehicle(double _mass, double _Cdrag, double _A, double _gearRatio, double _diffRatio, double _wheelRadius);

	//member functions
	double accel(double dt);
	double velocity(double dt);
	~Vehicle();


private:
	double mass;
	double Cdrag;
	double Crr;
	double currVelocity;
	
	/* to be added later
	double A;
	double gearRatio;
	double diffRatio;
	double wheelRadius;
	double torque;
	static const double transEff;
	*/
};

const double transEff = 0.7;


#endif // VEHICLE_H_