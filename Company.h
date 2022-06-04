#pragma once
#include "NormalTruck.h"
#include "SpecialTruck.h"
#include "VIPTruck.h"
#include "Queue.h"
#include "TypeEnum.h"
#include "linkedList.h"

class UI;
using namespace std;
class Event;
class Company
{
	//Waiting cargos
	linkedList<Cargos*> Normal_Cargos, Special_Cargos, Cancelled_Cargos;// Cargos queues (for: Waiting, Cancelled, Moving, Delivered)
	Queue<Cargos*>  Delivered_Normal_Cargos, Delivered_Special_Cargos, Delivered_VIP_Cargos;
	priorityQueue<Cargos*> VIP_Cargos;
	priorityQueue<Truck*> VIP_Trucks;
	priorityQueue<Truck*> Normal_Trucks;
	priorityQueue<Truck*> Special_Trucks;
	priorityQueue<Truck*> Moving_Trucks, Loading_Trucks, Maintenance_Trucks;
	Queue<Event*> Events;
	int AutoP, MovingCargosCount, AutoPCount;

public:
	Company();
	~Company();
	/// <summary>
	/// This function resturns the first available truck in the queue specialization
	/// </summary>
	/// <returns></returns>
	Truck* getNextAvailableTruck(Type TruckType);
	void NightModeLists();
	void DayModeLists();

	/// This function enqueue the cargo in the company waiting lists
	/// </summary>
	/// <param name="Cargo"> Cargo pointer</param>
	/// <returns></returns>
	bool addCargo(Cargos* Cargo);
	bool addCancelledCargo(Cargos* Cargo);


	/*/// <summary>
	/// This function enqueue the cargo in the Normal company queue
	/// </summary>
	/// <param name="Cargo"> Cargo pointer</param>
	/// <returns></returns>
	bool addNormalCargo(Cargos* Cargo);
	/// <summary>
	/// This function enqueue the cargo in the Special company queue
	/// </summary>
	/// <param name="Cargo"> Cargo pointer</param>
	/// <returns></returns>
	bool addSpecialCargo(Cargos* Cargo);
	/// <summary>
	/// This function enqueue the cargo in the VIP company queue
	/// </summary>
	/// <param name="Cargo"> Cargo pointer</param>
	/// <returns></returns>
	bool addVIPCargo(Cargos* Cargo);*/

	Cargos* HasCargo(int id);
	/*Cargos* HasNormalCargo(int id);
	Cargos* HasSpecialCargo(int id);
	Cargos* HasVIPCargo(int id);*/

	/// <summary>
	/// Cancel the cargo with sent id from being loaded to a truck (Status: Waiting -> Cancelled)
	/// </summary>
	/// <param name="CargoType">Type of the cargo (VIP,NORMAL,SPECIAL)</param>
	/// <param name="id"> Cargo Id </param>
	/// <returns></returns>
	bool removeCargo(Cargos* c);
	/*bool removeNormalCargo(Cargos* c);
	bool removeSpecialCargo(Cargos* c);
	bool removeVIPCargo(Cargos* c);*/



	bool addEvent(Event* e);

	void ExecuteCurrentEvent();


	bool addTruck(Truck* truckPtr,int pri);
	void setAutoP(int Days);
	int getAutoP();

	bool isReadyForDelivery(Type TruckType, Type CargoType);

	void printWaitingCargos(UI * ui);
	void printMovingCargos(UI * ui);
	void printLoadingTrucks(UI * ui);
	void printEmptyTrucks(UI * ui);
	void printInCheckUpTrucks(UI * ui);
	void printDeliveredCargos(UI * ui);

	bool readInputFile(UI* ui);
	void printOutputFile(UI * ui);
	void simulateProgram(int Mode,UI * ui);
};





