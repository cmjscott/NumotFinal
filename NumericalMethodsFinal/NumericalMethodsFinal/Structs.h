#pragma once

#ifndef _INC_STRUCTS
#define _INC_STRUCTS

#include <map>
#include <string>
#include "engine.h"
#include "Transmission.h"
#include "Vehicle.h"



typedef enum {
	COMPONENT_TRANSMISSION,
	COMPONENT_ENGINE,
	COMPONENT_VEHICLE,
	COMPONENT_RESULTS,
}componentType_e;

struct componentSave
{
	std::map<componentType_e, std::string> registeredComponents;

	void registerComponent(componentType_e _component, std::string path)
	{
		registeredComponents.insert(std::pair<componentType_e, std::string>(_component, path)); 
	}
};


//NOT USED
//I DO NOT UNDERSTAND HOW THIS WORKS. FUCKING MAGIC, YO
template <class T> 
void* constructor() { return (void*)new T(); }

struct factory
{
	typedef void*(*constructor_t)();
	typedef std::map<std::string, constructor_t> map_type;
	map_type m_classes;

	template <class T>
	void register_class(std::string const& n)
	{
		m_classes.insert(std::make_pair(n, &constructor<T>));
	}

	void* construct(std::string const& n)
	{
		map_type::iterator i = m_classes.find(n);
		if (i == m_classes.end()) return 0; // or throw or whatever you want
		return i->second();
	}
};

extern factory componentFactory;

//NOT USED


#endif