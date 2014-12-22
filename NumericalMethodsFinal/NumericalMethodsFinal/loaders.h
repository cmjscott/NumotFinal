#pragma once

#ifndef _INC_LOADERS
#define _INC_LOADERS

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Transmission.h"
#include "engine.h"
#include "Vehicle.h"


namespace loaders
{
	std::vector<std::string> loadFile(std::string _fileName);
	Transmission loadTransmission(std::string _fileName);

} // namespace loaders


#endif