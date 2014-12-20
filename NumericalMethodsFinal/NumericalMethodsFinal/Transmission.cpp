#include "Transmission.h"


Transmission::Transmission(){}

Transmission::Transmission(std::vector<double> _gearRatios)
{
	gearRatios = _gearRatios;
	gearEtas.assign(gearRatios.size(),1);
	gearRatios.shrink_to_fit();

	shiftTime = 0;
	shifting = false;
	currentGearIndex = 0;
}

Transmission::Transmission(std::vector<double> _gearRatios, std::vector<double> _gearEtas)
{
	gearRatios = _gearRatios;
	gearEtas = _gearEtas;
	gearRatios.shrink_to_fit();

	shiftTime = 0;
	shifting = false;
	currentGearIndex = 0;
}

Transmission::~Transmission(){}


void Transmission::upshift()
{
	if (currentGearIndex + 1 < gearRatios.size())
		currentGearIndex++;
}

void Transmission::downshift()
{
	if (currentGearIndex > 0)
		currentGearIndex--;
}

double Transmission::getRatio() { return gearRatios[currentGearIndex]; }
