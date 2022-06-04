#pragma once
//AA
#include "priorityQueue.h"
/*
*
*		Normal Trucks Class interface
* 
*/


#include "Truck.h"

class NormalTruck : public Truck
{

	
	static int CheckupDuration; // Maintenance checkup duration (General for all trucks of the same type)

	priorityQueue<Cargos*> TruckCargos; // Cargos loaded in the truck

public:
	// Constructor (Default)
	/*
		Initiates a normal truck object
	*/
	NormalTruck();
	NormalTruck(int s, int c, bool ns);
	// ------------------------------------ Setters & Getters ------------------------------------ //
	

	
	// > Checkup
	static void setCheckup(int CH);
	static int getCheckup();

	// ------------------------------------ Class Functions ------------------------------------ //
	
	/// <summary>
	/// Loading new cargo type on the truck.
	/// (Note : Delivery interval is automatically updated here)
	/// </summary>
	/// <param name="c">Cargo that shoulf be loaded on the truck</param>
	/// <returns> Returns bool to check whether the function performed its function or not </returns>
	virtual bool addCargo(Cargos* c);

	/// <summary>
	/// Remove a loaded cargo
	/// (Note : Delivery interval is automatically updated here)
	/// </summary>
	/// <param name="id"> ID which is unique for a cargo</param>
	/// <returns> Returns bool to check whether the function performed its function or not </returns>
	virtual Cargos* removeCargo(int id);

	virtual Type getCargosType();

	virtual void print(UI*);

	virtual Cargos* removeFirstCargo();

	virtual bool isEmpty();

	virtual int getCargosCount();
	Time getFirstArrivingCargoTime();
	void SetMovingTime(Time t);
	
};

