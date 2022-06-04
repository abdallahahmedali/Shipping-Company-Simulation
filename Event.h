#pragma once
//AA
#include "Truck.h"
#include "Company.h"
#include "Cargos.h"


class Event
{
	int Id; // Unique id for cargo
	Time EventTime; // Event action time

public:
	// ------------------------------------ Setters & Getters ------------------------------------ //
	
	Time getEventTime() const;
	void setEventTime(Time t);

	int getId() const;
	void setId(int i);

	// ------------------------------------ Class Functions ------------------------------------ //
	/// <summary>
	/// Setting event default parameters
	/// </summary>
	/// <param name="ID">Cargo ID</param>
	/// <param name="ET">Event Time</param>
	Event(int ID, Time ET);
	/// <summary>
	/// Execution of the event actions
	/// </summary>
	virtual void ExecuteEvent(Company* cmp_ptr) = 0;
};

