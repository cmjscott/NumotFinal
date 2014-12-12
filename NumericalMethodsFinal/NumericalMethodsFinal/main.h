#pragma once

#include <iostream> //for cin/cout
#include <cmath> // for math stuff
#include <conio.h> // for _getch()
#include <vector> 
#include <fstream> //for file I/O
#include "Vehicle.h"
#include <string>
#include "utilityFunctions.h"
//#include "matlabFunctions.h"
#include "generateVehicle.h"



std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt, double _rho = 1);
std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt, double _rho);
std::vector<std::vector<double> > simulation4(Vehicle testVehicle, double _dt, double _rho, double _timeToFullThrottle = .2);
void functionalityDemonstration();
void matlabScript();