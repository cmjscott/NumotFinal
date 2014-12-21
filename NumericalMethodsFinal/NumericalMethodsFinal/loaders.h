#pragma once

#ifndef _INC_LOADERS
#define _INC_LOADERS

#include <iostream>
#include <vector>
#include <string>
#include "Transmission.h"
#include "engine.h"
#include "Vehicle.h"


namespace loaders
{
	Transmission loadTransmission(std::string _fileName);

} // namespace loaders


#endif