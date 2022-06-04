
//AA
#include "VIPTruck.h"
#include "UI.h"

int VIPTruck::CheckupDuration = 0;

VIPTruck::VIPTruck(int cap) :TruckCargos(cap) {
	setCapacity(0);
	setSpeed(0);
}
VIPTruck::VIPTruck(int s, int c, bool ns) :TruckCargos(c) {
	setCapacity(c);
	setSpeed(s);
	setIsWorkingNightShifts(ns);
}

// ------------------------------------ Setters & Getters ------------------------------------ //


void VIPTruck::setCheckup(int CH) {
	CheckupDuration = CH;
}
int VIPTruck::getCheckup() {
	return CheckupDuration;
}
// ------------------------------------ Class Functions ------------------------------------ //


bool VIPTruck::addCargo(Cargos* c) {
	// -> Adding new cargo to the truck cargos
	TruckCargos.enqueue(c,-(c->getDeliveryDistance()/getSpeed()));
	// -> Increment the total loading time for the cargo
	this->setTotalLoadingTime(this->getTotalLoadingTime() + c->getLoadingTime());
	// -> Update delivery interval by checking for the furthest distance
if (getfurthestDistance() < c->getDeliveryDistance()) {
		//setDeliveryInterval((getDeliveryInterval() - 2*(getfurthestDistance() - c->getDeliveryDistance())/getSpeed()) + c->getLoadingTime());
		setfurthestDistance(c->getDeliveryDistance());
		setDeliveryInterval(2*getfurthestDistance()/getSpeed()+getTotalLoadingTime());
		//setfurthestDistance(c->getDeliveryDistance());
	}
	else
	{//the unloading time wasn't added if in that case???
		setDeliveryInterval(getDeliveryInterval()+c->getLoadingTime());
	
	}
    c->setTruck(this);
	return true;
}

Cargos* VIPTruck::removeCargo(int id) {
	// -> Creating a temp queue for searching
	/*Cargos* Cargo = TruckCargos.getPtrTo(id);

	if (Cargo) {
		return TruckCargos.remove(Cargo);
	}

*/
	return nullptr;
}


void VIPTruck::print(UI* ui) {
	if (TruckCargos.getCount() > 0) {
		ui->printMessage(to_string(getId()) + "{");
		TruckCargos.print();
		ui->printMessage("}");
	}
	else {
		ui->printMessage("{" + to_string(getId()) + "}");
	}
}

Type VIPTruck::getCargosType() {
	return TruckCargos.peek()->getType();
}


Cargos* VIPTruck::removeFirstCargo() {
if (!TruckCargos.getCount()==0)
		return TruckCargos.dequeue();
	else return nullptr;
}

bool VIPTruck::isEmpty() {
		return (TruckCargos.getCount()==0);
}

int VIPTruck::getCargosCount() {
	return TruckCargos.getCount();
}
Time VIPTruck::getFirstArrivingCargoTime()
{ 
	if(TruckCargos.peek())
		return TruckCargos.peek()->getCDT();
	else return Time(100000000);
	
}
void VIPTruck::SetMovingTime(Time t)
{Truck::SetMovingTime(t);
int previousunloadingTime=0;
for(int i=1;i<=TruckCargos.getCount();i++){
	Cargos* cargo=TruckCargos.dequeue();
	
	cargo->setCDT(this->getMovingTime()+cargo->getDeliveryDistance()/this->getSpeed() + cargo->getLoadingTime() + previousunloadingTime);
	previousunloadingTime+=cargo->getLoadingTime();
	TruckCargos.enqueue(cargo,-1000*i);

}
}