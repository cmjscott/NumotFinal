#pragma once

#include <iostream> //for cin/cout
#include <cmath> // for math stuff
#include <conio.h> // for _getch()
#include <vector> 
#include <fstream> 
#include <iterator>
#include "Vehicle.h"
#include <string>
#include "utilityFunctions.h"
#include "matlabFunctions.h"



std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double dt, double _rho);
std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt, double _rho);