#include "SpecialTruck.h"
#include "UI.h"
//AA

int SpecialTruck::CheckupDuration = 0;

SpecialTruck::SpecialTruck() :TruckCargos(50){
	setCapacity(0);
	setSpeed(0);
}
SpecialTruck::SpecialTruck(int s, int c, bool ns) :TruckCargos(c){
	setCapacity(c);
	setSpeed(s);
	setIsWorkingNightShifts(ns);
}
// ------------------------------------ Setters & Getters ------------------------------------ //




void SpecialTruck::setCheckup(int CH) {
	CheckupDuration = CH;
}
int SpecialTruck::getCheckup() {
	return CheckupDuration;
}

// ------------------------------------ Class Functions ------------------------------------ //


bool SpecialTruck::addCargo(Cargos* c) {
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

Cargos* SpecialTruck::removeCargo(int id) {
	// -> Creating a temp queue for searching
	/*Cargos* Cargo = TruckCargos.getPtrTo(id);

	if (Cargo) {
		return TruckCargos.remove(Cargo);
	}*/


	return nullptr;
}

void SpecialTruck::print(UI* ui) {
	if (TruckCargos.getCount() > 0) {
		ui->printMessage(to_string(getId()) + "(");
		TruckCargos.print();
		ui->printMessage(")");
	}
	else {
		ui->printMessage("(" + to_string(getId()) + ")");
	}
}

Type SpecialTruck::getCargosType() {
	return TruckCargos.peek()->getType();
}


Cargos* SpecialTruck::removeFirstCargo() {
	if (!TruckCargos.getCount()==0)
		return TruckCargos.dequeue();
	else return nullptr;
}

bool SpecialTruck::isEmpty() {
	return (TruckCargos.getCount()==0);
}

int SpecialTruck::getCargosCount() {
	return TruckCargos.getCount();
}
Time SpecialTruck::getFirstArrivingCargoTime()
{ 
	if(TruckCargos.peek())
		return TruckCargos.peek()->getCDT();
	else return Time(100000000);
	
}
void SpecialTruck::SetMovingTime(Time t)
{Truck::SetMovingTime(t);
int previousunloadingTime=0;
for(int i=1;i<=TruckCargos.getCount();i++){
	Cargos* cargo=TruckCargos.dequeue();
	
	cargo->setCDT(this->getMovingTime()+cargo->getDeliveryDistance()/this->getSpeed() + cargo->getLoadingTime() + previousunloadingTime);
	previousunloadingTime+=cargo->getLoadingTime();
	TruckCargos.enqueue(cargo,-1000*i);

}
}