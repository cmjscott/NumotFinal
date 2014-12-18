#include "main.h"

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



const double MS_TO_MPH(2.2368);

int main()
{
	std::vector<std::vector<double> > test1Data, test2Data, test3Data, test4Data, testData;
	std::vector<double> time, vel, gearRatios= { 2.785, 1.545, 1, .697 };
	std::string fileName;
	double rho, dt, timeToFullThrottle;
	int simulationFlag(99);				//get rid of default value later. for test purposes
	Vehicle simulationVehicle;

	//gearRatios.assign(ratioValues, ratioValues + sizeof(ratioValues) / sizeof(double));


	//prompts user to chose a simulation and then prompts them for each required input.
	do
	{
		//std::cout << "Which simulation would you like to run? (1, 2, 3, 4)" << std::endl;
		//simulationFlag = util::getSanitizedInput<int>(1,4);
		//std::cout << std::endl;
		
		if (simulationFlag == 99)
		{
			functionalityDemonstration();
			std::cout << "Demonstration simulations complete, press any key to quit";
			_getch();
			return 0;
		}
		

		std::cout << std::endl << "Enter time step (dt): ";
		dt = util::getSanitizedInput<double>();
		std::cout << std::endl;

		//creates a test vehicle based on simulation value entered
		simulationVehicle = generateVehicle(simulationFlag);
		
		if (simulationFlag != 1)
		{
			std::cout << std::endl << "Enter air density rho (kg/m^3): ";
			rho = util::getSanitizedInput<double>();
			simulationVehicle.setRho(rho);
		}

		//based on the simulation value entered, runs the corrisponding simulation
		switch (simulationFlag)
		{
		case 1:
			testData = simulation1(simulationVehicle, dt);
			break;
		case 2:
			testData = simulation1(simulationVehicle, dt);
			break;
		case 3:
			testData = simulation3(simulationVehicle, dt);
			break;
		case 4:
			std::cout << std::endl << "Enter time to full throttle: ";
			timeToFullThrottle = util::getSanitizedInput<double>();
			std::cout << std::endl;
			testData = simulation4(simulationVehicle, dt, timeToFullThrottle);
			break;
		}

		//promps user if they want to save the simulation data
		if (util::yesNo("Write results to file?"))
		{
			std::cout << std::endl << "Enter name of data file: ";
			fileName = util::getSanitizedInput<std::string>();

			util::outputData(testData, fileName);
		}


	} while (util::yesNo("Run another simulation?")); //loop back through code and run another simulation.

	std::cout << "Simulations complete, press any key to quit";
	_getch();

	return 0;
}

std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double zeroToSixtyTime(0);
	
	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	std::cout << "-------------------------------Simulation 1 and 2-------------------------------" << std::endl;

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while ((vel.back() - vel.rbegin()[1])/_dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	std::cout << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * MS_TO_MPH << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}

std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel;
	double maxSpeed, timeMaxSpeed, zeroToSixtyTime(0);


	//Sets initial time and velocity.
	time.push_back(0);
	vel.push_back(0);

	std::cout << "----------------------------------Simulation 3----------------------------------" << std::endl;

	do
	{
		vel.push_back(testVehicle.velocity(vel.back(), _dt));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

	} while ((vel.back() - vel.rbegin()[1]) / _dt > .0001); // keep calculating velocity until the acceleration is less than .0001 (essentially at max velocity)

	maxSpeed = vel.back();
	timeMaxSpeed = time.back();
	
	do
	{
		vel.push_back(testVehicle.brake(vel.back(), _dt));
		time.push_back(time.back() + _dt);
	} while (vel.back() > 0);

	if (vel.back() < 0)
		vel.back() = 0;

	std::cout << "Your maximum velocity was " << maxSpeed << " m/s  (" << maxSpeed * MS_TO_MPH << " mph)\n";
	std::cout << "Time to reach maximum velocity: " << time.back() << "seconds." << std::endl;
	std::cout << "Time to come to a complete stop: " << time.back() - timeMaxSpeed << "seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	return data;
}

std::vector<std::vector<double> > simulation4(Vehicle testVehicle, double _dt, double _timeToFullThrottle)
{
	std::vector<std::vector<double> > data;
	std::vector<double> time, vel, rpm, force, torque;
	double throttle(0), zeroToSixtyTime(0);

	const double timeToFullThrottle = _timeToFullThrottle;

	//Sets initial values
	time.push_back(_dt);
	vel.push_back(0);
	//rpm.push_back(0);
	//force.push_back(0);
	//torque.push_back(0);

	std::cout << "----------------------------------Simulation 4----------------------------------" << std::endl;

	do
	{
		throttle = time.back()/timeToFullThrottle;
		vel.push_back(testVehicle.velocity(vel.back(), _dt, throttle));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

		//rpm.push_back(testVehicle.getRPM());
		//force.push_back(testVehicle.engineDriveForce(throttle));
		//torque.push_back(testVehicle.getTorque(throttle));
	} while (time.back() < timeToFullThrottle);

	do
	{ 
		vel.push_back(testVehicle.velocity(vel.back(), _dt, throttle));
		time.push_back(time.back() + _dt);

		if (vel.back() * MS_TO_MPH >= 60 && zeroToSixtyTime == 0)
			zeroToSixtyTime = time.back();

		//rpm.push_back(testVehicle.getRPM());
		//force.push_back(testVehicle.engineDriveForce(throttle));
		//torque.push_back(testVehicle.getTorque(throttle));
	} while ((vel.back() - vel.rbegin()[1]) / _dt > .1); // keep calculating velocity until the acceleration is less than .01 (essentially at max velocity)

	std::cout << std::endl << "Your maximum velocity was " << vel.back() << " m/s  (" << vel.back() * MS_TO_MPH << " mph)" << std::endl;
	std::cout << "Time to reach maximum throttle position: " << timeToFullThrottle << " seconds." << std::endl;
	std::cout << "Time to reach maximum velocity: " << time.back() << " seconds." << std::endl;
	std::cout << "0 - 60 time: " << zeroToSixtyTime << " seconds." << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl << std::endl;

	data.push_back(time);
	data.push_back(vel);
	//data.push_back(rpm);
	//data.push_back(force);
	//data.push_back(torque);
	return data;
}

void functionalityDemonstration()
{
	/*NOTE: Using 2001 Subaru legacy outback wagon, LL bean eddition for default simulation
	Cd = .32
	A = 23.4 ft^2 = 2.1739 m^2
	mass = 3715 lbs = 1685.1 kg
	Drive force ~ 1500 N
	Braking force ~ 7700 N
	Gear Ratios:
	1st 2.785
	2nd 1.545
	3rd 1.000
	4th 0.697
	Rev 2.272
	Diff 4.11

	Tires: 225/60R16 98H SL
	wheelRadius = 0.33782 m
	
	RPM =    { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	torque = { 240 , 250 , 260 , 270 , 280 , 290 , 300 , 305 , 310 , 305 , 295 , 285 , 280 , 270 , 260  };
	*/
	std::vector<std::string> v;
	std::vector<std::vector<double> > test4Data;
	std::vector<double> revMap = { 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4000, 4400, 4800, 5200, 5600, 6000, 6400, 6800 };
	std::vector<double> torqueMap = { 240, 250, 260, 270, 280, 290, 300, 305, 310, 305, 295, 285, 280, 270, 260 };
	std::vector<double> gearRatios = { 2.785, 1.545, 1, .697 };
	double rho(1.2041), dt(.001), mass(1685.1), Cdrag(.32), driveForce(1700), frontArea(2.1739), brakingForce(7700), diffRatio(4.11), wheelRadius(.33782);

	//create vehicle objects for each simulation
	Vehicle testVehicle(mass, Cdrag, frontArea, gearRatios, diffRatio, wheelRadius, rho);
	engine* testEngine = new engine(revMap, torqueMap);

	testVehicle.attachEngine(testEngine);

	//Run simulations
	test4Data = simulation4(testVehicle, dt);
	
	//std::cout << revMap << std::endl;
	//_getch();

	//Output data for matlab
	util::outputData(test4Data, "test_data");
	//util::outputData(test2Data, "simulation_2_example_data");
	//util::outputData(test3Data, "simulation_3_example_data");
	//util::outputData(test4Data, "simulation_4_example_data");

}

void testCase();

