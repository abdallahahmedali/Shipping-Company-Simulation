#pragma once
//AA
#include "Event.h"
#include "TypeEnum.h"


/*
	Ready event class interface
*/
class ReadyEvent : public Event
{
	Type CargoType; // Type of the cargo (Enum)
	int Distance; // Distance in Km
	int LoadTime; // Time of loading cargo in hours 
	int Cost; // Cost of the cargo

public:
	/// <summary>
	/// Constructor for reading Ready Event parameters
	/// </summary>
	/// <param name="T">Cargo type</param>
	/// <param name="D">Distance</param>
	/// <param name="LT">Load time</param>
	/// <param name="C">Cargo cost</param>
	/// <param name="ID">Cargo ID</param>
	/// <param name="ET">Event time</param>
	ReadyEvent(Type T, float D, int LT, int C, int ID, Time ET);

	virtual void ExecuteEvent(Company* cmp_ptr);


};

