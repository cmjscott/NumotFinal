#include "Transmission.h"


Transmission::Transmission(){}

Transmission::Transmission(std::vector<double> _gearRatios)
{
	gearRatios = _gearRatios;
	gearEtas.assign(gearRatios.size(),1);
}

Transmission::Transmission(std::vector<double> _gearRatios, std::vector<double> _gearEtas)
{
	gearRatios = _gearRatios;
	gearEtas = _gearEtas;

}

Transmission::~Transmission(){}