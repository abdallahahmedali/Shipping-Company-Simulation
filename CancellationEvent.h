#pragma once
//AA
#include "Event.h"
#include "TypeEnum.h"

/*
	Cancellation event class interface
*/
class CancellationEvent : public Event
{
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
	CancellationEvent(int ID, Time ET);

	virtual void ExecuteEvent(Company* cmp_ptr);


};

