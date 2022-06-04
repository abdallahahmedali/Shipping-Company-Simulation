#pragma once
//AA
#include "Event.h"
#include "TypeEnum.h"


/*
	Promotion event class interface
*/
class PromotionEvent : public Event
{
	int ExtraMoney; // Extra money for the promotion
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
	PromotionEvent(int EM, int ID, Time ET);

	virtual void ExecuteEvent(Company* cmp_ptr);


};

