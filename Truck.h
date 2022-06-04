#pragma once
//AA
#include "Cargos.h"
#include "Time.h"
#include "linkedList.h"
/*
*
*		Trucks Class interface (Abstract class)
*
*/

using namespace std;
class UI;
class Truck
{
	static int JourneysMaxNum; // Maximum allowed number of journeys made by a truck to have its maintenance check
	static int TruckCounter; // Counter for current declared trucks
	/*

	> Delivery interval of the truck
		DeliveryInterval = (Delivery Distance of furthest cargo)/truck speed + Sum of unload times of all its cargos + time to come back

	*/
	float DeliveryInterval;
	int JourneysMade; // No. of journey made by the truck (To compare with JourneyMaxNum)
	int TID; //Truck Id

	int TotalLoadingTime;
	float furthestDist;
	int TDC; // Total delivered cargos by truck

	bool isAvailable; // State of availability (0 -> False "EX : Maintenance or on delivery" | 1 -> True "Available for loading")
	Time NextAvailablility; // Next time of availability (Calculated automatically based on factors |(DeliveryInterval, CheckupDuration)|)
	bool isLoading;
	Time MovingTime;

	int TotalActiveTime;
	bool isWorkingNightShifts; // Night shifts

	int Capacity; // Capacity of the truck (General for all trucks of the same type) # of cargos
	int Speed; // Speed of the truck (General for all trucks of the same type)

public:
	Truck();

	// ------------------------------------ Setters & Getters ------------------------------------ //
		// > Capacity
	void setCapacity(int C);
	int getCapacity();

	// > Speed
	void setSpeed(int S);
	int getSpeed();



	static int getJourneysMax();
	static void setJourneysMax(int j);

	void setIsWorkingNightShifts(bool a);
	bool getIsWorkingNightShifts();

	// > Delivery Interval 
	float getDeliveryInterval();
	void setDeliveryInterval(float DI);

	// > Availability
	void setIsAvailable(bool a);
	bool getIsAvailable();

	void setIsLoading(bool a);
	bool getIsLoading();

	void SetNextAvailability(Time t);
	Time getNextAvailability() const;

	virtual void SetMovingTime(Time t);
	Time getMovingTime();

	int getTotalLoadingTime()const;
	void setTotalLoadingTime(int LT);

	float getfurthestDistance()const;
	void setfurthestDistance(float FD);

	int getId() const;

	int getJourneysMade();
	int getTDC() const;

	void setTotalActiveTime(int h);
	int getTotalActiveTime();

	void resetTruck();
	// ------------------------------------ Class Functions (Some are pure virtual) ------------------------------------ //

	/// <summary>
	/// Loading new cargo type on the truck.
	/// (Note : Delivery interval is automatically updated here)
	/// </summary>
	/// <param name="c">Cargo that should be loaded on the truck</param>
	/// <returns> Returns bool to check whether the function performed its function or not </returns>
	virtual bool addCargo(Cargos* c) = 0;

	/// <summary>
	/// Remove a loaded cargo
	/// (Note : Delivery interval is automatically updated here)
	/// </summary>
	/// <param name="id"> ID which is unique for a cargo</param>
	/// <returns> Returns bool to check whether the function performed its function or not </returns>
	virtual Cargos* removeCargo(int id) = 0;

	void incrementJourneysMade();
	void incrementTDC();

	virtual Type getCargosType() = 0;

	virtual void print(UI*) = 0;
	virtual Cargos* removeFirstCargo() = 0;
	virtual bool isEmpty() = 0;
	virtual int getCargosCount() = 0;
	virtual Time getFirstArrivingCargoTime()=0;
};

