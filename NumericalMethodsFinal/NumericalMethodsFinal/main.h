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

#pragma comment ( lib , "libmat.lib")
#pragma comment ( lib , "libmx.lib")
#pragma comment ( lib , "libmex.lib")
#pragma comment ( lib , "libeng.lib")


std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double dt, double _rho);