#pragma once

#ifndef _INC_MAIN
#define _INC_MAIN

#include <iostream> //for cin/cout
#include <cmath> // for math stuff
#include <conio.h> // for _getch()
#include <vector> 
#include <fstream> //for file I/O
#include <string>
#include <Windows.h>
#include "utilityFunctions.h"
//#include "matlabFunctions.h"
#include "generators.h"
#include "prettyprint.h"
#include "Vehicle.h"
#include "savers.h"
#include "loaders.h"
#include "Structs.h"

extern componentSave components;

std::vector<std::vector<double> > simulation1(Vehicle testVehicle, double _dt);
std::vector<std::vector<double> > simulation3(Vehicle testVehicle, double _dt);
std::vector<std::vector<double> > simulation4(Vehicle testVehicle, double _dt, double _timeToFullThrottle = .2);
void functionalityDemonstration();
void init();

#endif