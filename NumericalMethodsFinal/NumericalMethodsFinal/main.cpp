#include "main.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

const double staticRho(1);
const double dt(.001); 
const double msToMph(2.2368);

int main()
{
	std::vector<std::vector<double> > test1Data, test2Data, test3Data, test4Data;
	std::vector<double> time, vel, gearRatios; 
	double rho(1.2041);
	double ratioValues[] = { 2.785, 1.545, 1, .697 };
	
	std::vector<double> revMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	std::vector<double> torqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };

	gearRatios.assign(ratioValues, ratioValues + sizeof(ratioValues) / sizeof(double));

	/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for testing
	Cd = .32
	A = 23.4 ft^2 = 2.1739 m^2
	mass = 3715 lbs = 1685.1 kg
	Drive force ~ 1500 N
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

	//create vehicle objects for the simulation
	Vehicle SubaruSim1(1685.1, .32, 1700);
	Vehicle SubaruSim2(1685.1, .32, 1700, 2.1739);
	Vehicle SubaruSim3(1685.1, .32, 1700, 2.1739, 7700);
	Vehicle SubaruSim4(1685.1, .32, 2.1739,gearRatios,4.11,.33782,revMap,torqueMap);

	//Run simulations
	//test1Data = simulation1(SubaruSim1, dt, staticRho);
	//test2Data = simulation1(SubaruSim2, dt, rho);
	//test3Data = simulation3(SubaruSim3, dt, rho);
	test4Data = simulation4(SubaruSim4, dt, rho);

	//Output data for matlab
	//util::outputData(test1Data, "sim1");
	//util::outputData(test2Data, "sim2");
	//util::outputData(test3Data, "sim3");
	util::outputData(test4Data, "sim4");


	/*
	//graph data in matlab

	Engine *m_pEngine; //name the matlab engine variable
	m_pEngine = engOpen("null"); //open an instance of the matlab engine

	vecToMatlab(m_pEngine, test1Data[0], "time1");
	vecToMatlab(m_pEngine, test1Data[1], "velocity1");

	vecToMatlab(m_pEngine, test2Data[0], "time2");
	vecToMatlab(m_pEngine, test2Data[1], "velocity2");

	vecToMatlab(m_pEngine, test3Data[0], "time3");
	vecToMatlab(m_pEngine, test3Data[1], "velocity3");

	vecToMatlab(m_pEngine, test4Data[0], "time4");
	vecToMatlab(m_pEngine, test4Data[1], "velocity4");
	vecToMatlab(m_pEngine, test4Data[2], "rpm4");
	vecToMatlab(m_pEngine, test4Data[3], "torque4");


	engEvalString(m_pEngine, "figure('name','Simulation 1 and 2')"); // opens up matlab figure window
	engEvalString(m_pEngine, "hold on");
	engEvalString(m_pEngine, "plot(time1,velocity1, 'r')");
	engEvalString(m_pEngine, "plot(time2,velocity2, 'b')");
	engEvalString(m_pEngine, "hold off");

	engEvalString(m_pEngine, "figure('name','Simulation 3')"); // opens up matlab figure window
	engEvalString(m_pEngine, "hold on");
	engEvalString(m_pEngine, "plot(time3,velocity3, 'b')");
	engEvalString(m_pEngine, "hold off");
	*/

	

	std::cout << "Simulations complete, press any key to quit";
	_getch();
	//engClose(m_pEngine);

	_getch();
	return 0;
}

std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt, double _rho)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	
	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &_rho));
		time.push_back(time.back() + _dt);
	} while ((vel.back() - vel.rbegin()[1])/_dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	std::cout << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * msToMph << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}

std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt, double _rho)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double maxSpeed, timeMaxSpeed;


	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &_rho));
		time.push_back(time.back() + _dt);
	} while ((vel.back() - vel.rbegin()[1]) / _dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	maxSpeed = vel.back();
	timeMaxSpeed = time.back();
	
	do
	{
		vel.push_back(testVehicle.brake(vel.back(), _dt, &_rho));
		time.push_back(time.back() + _dt);
	} while (vel.back() > 0);

	if (vel.back() < 0)
		vel.back() = 0;

	std::cout << "Your maximum velocity was " << maxSpeed << " m/s  (" << maxSpeed * msToMph << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;
	std::cout << "Time to come to a complete stop: " << time.back() - timeMaxSpeed << "seconds." << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}

std::vector<std::vector<double> > simulation4(Vehicle testVehicle, double _dt, double _rho)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel, rpm, force, torque;
	const double timeToFullThrottle(5);
	double maxSpeed, timeMaxSpeed, throttle(0);

	//Sets initial values
	time.push_back(0);
	vel.push_back(0);
	rpm.push_back(0);
	force.push_back(0);
	torque.push_back(0);

	for (int i = 0; i < timeToFullThrottle / _dt; ++i)
	{
		throttle = i / (timeToFullThrottle / _dt);
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &_rho, throttle));
		time.push_back(time.back() + _dt);
		rpm.push_back(testVehicle.pubGetRPM());
		force.push_back(testVehicle.engineDriveForce(throttle));
		torque.push_back(testVehicle.getTorque(throttle));
	}

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt, &_rho, throttle));
		time.push_back(time.back() + _dt);
		rpm.push_back(testVehicle.pubGetRPM());
		force.push_back(testVehicle.engineDriveForce(throttle));
		torque.push_back(testVehicle.getTorque(throttle));
	} while ((vel.back() - vel.rbegin()[1]) / _dt > .1); // keep calculating velocity until the acceleration is less than .01 (essentially at max velocity)

	std::cout << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * msToMph << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;

	data.push_back(time);
	data.push_back(vel);
	data.push_back(rpm);
	data.push_back(force);
	data.push_back(torque);
	return data;
}