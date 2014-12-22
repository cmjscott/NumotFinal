#include "engine.h"



engine::engine(){}

engine::engine(std::vector<double> _rpm, std::vector<double> _torque, std::string _name, double _efficiencyFactor)
{
	rpm = _rpm;
	torque = _torque;
	name = _name;
	efficiencyFactor = _efficiencyFactor;
	maxRpm = rpm.back();
	peakTorqueRpm = findPeakTorqueRpm();
}

engine::~engine() {}


double engine::findPeakTorqueRpm()
{
	int i = 1;

	while (torque[i] > torque[i - 1])
		i++;

	return rpm[i-1];
}

//finds the rpm value where peak torque is generated on the torque curve
double engine::getTorque(double currentRpm)
{
	double currTorque;
	int i = 0;

	// does a linear search on the rpm vector in the torque to get the position of the current rpm on the torque curve
	do
		i++;
	while (currentRpm > rpm[i]);

	//linear interpolation of current rpm on the torque curve
	currTorque = torque[i - 1] + (currentRpm - rpm[i - 1]) * (torque[i] - torque[i - 1]) / (rpm[i] - rpm[i - 1]);
	return currTorque;
}

std::ostream& operator << (std::ostream& out, const engine& obj)
{
	out << "Engine" << std::endl;
	out << obj.name << std::endl;
	out << "Rpm:";
	for (auto i : obj.rpm)
		out << i << ",";
	out << std::endl;

	out << "Torque:";
	for (auto i : obj.torque)
		out << i << ",";
	out << std::endl;

	out << "Efficiency factor:" << obj.efficiencyFactor << std::endl;

	return out;
}