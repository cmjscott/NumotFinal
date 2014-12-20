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

Vehicle::Vehicle() {}

//constructor for sim 1
Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	Crr = 30 * Cdrag;
	frontArea = 2; // Used for simulation 1 where the .5 coefficient must be neutralized.
	simulationFlag = 1;
}

//constructor for sim 2
Vehicle::Vehicle(double _mass, double _Cdrag, double _fDrive, double _frontalArea)
{
	mass = _mass;
	Cdrag = _Cdrag;
	fDrive = _fDrive;
	frontArea = _frontalArea;
	Crr = 30 * Cdrag;
	simulationFlag = 2;
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
	simulationFlag = 3;
}

//constructor for sim 4
Vehicle::Vehicle(double _mass, double _Cdrag, double _frontalArea, std::vector<double> _gearRatios,
	double _diffRatio, double _wheelRadius, double _rho)
{
	mass = _mass;
	Cdrag = _Cdrag;
	frontArea = _frontalArea;
	Crr = 30 * Cdrag;
	diffRatio = _diffRatio;
	wheelRadius = _wheelRadius;	
	gearRatios = _gearRatios;
	rho = _rho;
	transEff = .7;
	currGear = 1;
	simulationFlag = 4;
}

Vehicle::~Vehicle() {}
 
//Getters and Setters
void Vehicle::setRho(double _rho) { rho = _rho; }
void Vehicle::attachEngine(engine* _engine) { attachedEngine = _engine; }

std::vector<double> Vehicle::simulateNextTimestep(double _currVelocity, double _dt, double _throttle)
{
	currVelocity = _currVelocity;
	dt = _dt;
	currentThrottle = _throttle;
	velocityHolder = accelerationHolder = torqueHolder = rpmHolder = 0;

	velocityHolder = velocity();

	//TODO: add error checking to this in case one of the variables doesn't get set properly and remains zero.
	stateData.push_back(velocityHolder);
	stateData.push_back(accelerationHolder);
	stateData.push_back(torqueHolder);
	stateData.push_back(rpmHolder);

	return stateData;
}

//Returns the next velocity after dt time has passed, based on current velocity
double Vehicle::velocity()
{
	accelerationHolder = accel();
	return currVelocity + dt * accelerationHolder;
}

double Vehicle::brake()
{
	accelerationHolder = deccel();
	return currVelocity + dt * accelerationHolder;
}

//calculates the acceleartion based on the sum of the forces on the car and the mass
double Vehicle::accel()
{
	double fSum;
	if (currentThrottle == -1)
		fSum = fDrive + fDrag() + Frr();
	else
	{
		fSum = engineDriveForce() + fDrag() + Frr();
		shift();
	}
	return fSum / mass;
}

//calculates the force on the vehicle due to braking
double Vehicle::deccel()
{
	double fSum;
	fSum = -fBrake + fDrag() + Frr();
	return fSum / mass;
}

double Vehicle::fDrag() { return -0.5 * Cdrag * frontArea * rho * std::pow(currVelocity, 2); }//calculates the aerodynamic drag forces

double Vehicle::Frr(){ return -Crr * currVelocity;}//calculates the rolling resistances

//calculates the drive force based on throttle and torque
double Vehicle::engineDriveForce() 
{
	torqueHolder = attachedEngine->getTorque(getRPM());
	return torqueHolder * currentThrottle * gearRatios[currGear-1] * diffRatio * transEff / wheelRadius;
}

//figures out if the car should shift or not.
//TODO: move shifting functionality to the gearbox instead of the car? not sure how I want to handle shifting yet
void Vehicle::shift()
{	
	//will do nothing if the current gear is equal to the number of gears in the gearbox
	if (currGear >= gearRatios.size()) 
		return;

	double currentRPM, upshiftedRPM;
	currentRPM = getRPM();

	//calculates the rpm value at the current speed if the gear were increased to the next gear
	//TODO: change the rpm function from using the current gear to taking a gear index as a parameter
	upshiftedRPM = currVelocity / wheelRadius *(60 / (2 * M_PI)) * gearRatios[currGear] * diffRatio;

	if ((currentRPM - upshiftedRPM) / 2 >= (attachedEngine->peakTorqueRpm - upshiftedRPM))
	{
		currGear++;

		if (currGear == 2)
			std::cout << "Shifted to 2nd gear at " << currentRPM << " rpm." << std::endl;
		else if (currGear == 3)
			std::cout << "Shifted to 3rd gear at " << currentRPM << " rpm." << std::endl;
		else 
			std::cout << "Shifted to " << currGear << "th gear at " << currentRPM << " rpm." << std::endl;
	}
}

//calculates the current rpm based on current velocity and gear ratio. 
double Vehicle::getRPM()
{
	//TODO: change the minimum rpm to a settable attribute either in the engine or the car itself.
	rpmHolder = currVelocity / wheelRadius *(60 / (2 * M_PI)) * gearRatios[currGear-1] * diffRatio;
	if (rpmHolder < 3000 && currGear == 1)
		rpmHolder = 3000;
	if (rpmHolder > attachedEngine->maxRpm)
		rpmHolder = attachedEngine->maxRpm;

	//added this because I wasn't sure if it was alright to return a class variable or not.
	double rpm = rpmHolder;
	return rpm;
}

std::ostream& operator << (std::ostream& out, const Vehicle& obj)
{
	/*
	mass
	Cdrag
	frontArea
	Crr
	diffRatio = _diffR
	wheelRadius = _wheelRadius;
	gearRatios = _gearRatios;
	revMap = _revMap;
	torqueMap = _torqueMap;
	rho = _rho;
	*/
	return out;
}

