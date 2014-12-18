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
Vehicle::Vehicle(double _mass, double _Cdrag, double _frontalArea, std::vector<double> _gearRatios, double _diffRatio, double _wheelRadius,
	std::vector<double> _revMap, std::vector<double> _torqueMap, double _rho)
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
	rho = _rho;
	currGear = 1;
	simulationFlag = 4;
	peakTorqueIndex = findPeakTorque();
}


//Honestly not 100% sure what this does.
Vehicle::~Vehicle() {}
 

//Getters and Setters
void Vehicle::setRho(double _rho) { rho = _rho; }



//Returns the next velocity after dt time has passed, based on current velocity
double Vehicle::velocity(double _currVelocity, double dt, double throttle)
{
	double acceleration;
	currVelocity = _currVelocity;
	if (throttle == -1)
		acceleration = accel();
	else
		acceleration = accel(throttle);

	return currVelocity + dt * acceleration;
}

double Vehicle::brake(double _currVelocity, double dt)
{
	double acceleration;
	currVelocity = _currVelocity;
	acceleration = deccel();

	return currVelocity + dt * acceleration;
}

//calculates the acceleartion based on the sum of the forces on the car and the mass
double Vehicle::accel(double throttle)
{
	double fSum;
	if (throttle == -1)
		fSum = fDrive + fDrag() + Frr();
	else
	{
		fSum = engineDriveForce(throttle) + fDrag() + Frr();
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
double Vehicle::engineDriveForce(double throttle) { return getTorque(throttle) * throttle * gearRatios[currGear-1] * diffRatio * transEff / wheelRadius; }


//figures out if the car should shift or not.
void Vehicle::shift()
{	
	//will do nothing if the current gear is equal to the number of gears in the gearbox
	if (currGear >= gearRatios.size()) 
		return;

	double currentRPM, upshiftedRPM;
	currentRPM = getRPM();

	//calculates the rpm value at the current speed if the gear were increased to the next gear
	upshiftedRPM = currVelocity / wheelRadius *(60 / (2 * M_PI)) * gearRatios[currGear] * diffRatio;

	if ((currentRPM - upshiftedRPM) / 2 >= (revMap[peakTorqueIndex] - upshiftedRPM))
	{
		++currGear;

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
	double rpm;
	rpm = currVelocity / wheelRadius *(60 / (2 * M_PI)) * gearRatios[currGear-1] * diffRatio;
	if (rpm < 3000 && currGear == 1)
		rpm = 3000;
	if (rpm > revMap.back())
		rpm = revMap.back();

	return rpm;
}

//calculates torque based on current rpm and throttle position
double Vehicle::getTorque(double throttle)
{
	double currentRPM, currTorque;
	int i = 0;

	currentRPM = getRPM();	

	// does a linear search on the rpm vector in the torque to get the position of the current rpm on the torque curve
	do
		++i;
	while (currentRPM < revMap[i]);

	//linear interpolation of current rpm on the torque curve
	currTorque = torqueMap[i - 1] + (currentRPM - revMap[i - 1]) * (torqueMap[i] - torqueMap[i - 1]) / (revMap[i] - revMap[i - 1]);

	return currTorque;
}

//finds the rpm value where peak torque is generated on the torque curve
int Vehicle::findPeakTorque()
{
	int i = 0;

	do
		++i;
	while (torqueMap[i] > torqueMap[i-1]);

	return i - 1;
}

std::ostream& operator << (std::ostream& out, const Vehicle& obj)
{

	return out;
}

