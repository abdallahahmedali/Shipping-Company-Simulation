
#include "ReadyEvent.h"

ReadyEvent::ReadyEvent(enum Type T, float D, int LT, int C, int ID, Time ET ) : Event(ID, ET) {
	CargoType = T;
	Distance = D;
	LoadTime = LT;
	Cost = C;
}

void ReadyEvent::ExecuteEvent(Company* cmp_ptr) {
	/*
	Allocating new cargo with these parameters and return it to company to add it to its queue
	*/
	Cargos* Cargo;
	// -> Setting the attributes (Recommended a constructor) with a non-default constructor during the allocation
	Cargo = new Cargos(CargoType, getEventTime(), getId(), Distance, LoadTime, Cost);
	// -> Sending the cargo address to Company Class to enqueue it
	cmp_ptr->addCargo(Cargo);
}