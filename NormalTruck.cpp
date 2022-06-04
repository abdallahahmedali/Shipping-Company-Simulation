//AA
#include "NormalTruck.h"
#include "UI.h"


int NormalTruck::CheckupDuration = 0;

NormalTruck::NormalTruck() :TruckCargos(50){
	setCapacity(0);
	setSpeed(0);
}

NormalTruck::NormalTruck(int s, int c, bool ns) : TruckCargos(c) {
	setCapacity(c);
	setSpeed(s);
	setIsWorkingNightShifts(ns);
}

// ------------------------------------ Setters & Getters ------------------------------------ //





void NormalTruck::setCheckup(int CH) {
	CheckupDuration = CH;
}
int NormalTruck::getCheckup() {
	return CheckupDuration;
}
// ------------------------------------ Class Functions ------------------------------------ //

bool NormalTruck::addCargo(Cargos* c) {
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
	// adding the truck pointer to the cargo info
	c->setTruck(this); 
	return true;
}

Cargos* NormalTruck::removeCargo(int id){
	// -> Creating a temp queue for searching
	//Cargos* Cargo = TruckCargos.getPtrTo(id);

	//if (Cargo) {
	//	return TruckCargos.remove(Cargo);
	//}
	return nullptr;
}

void NormalTruck::print(UI* ui) {
	if (TruckCargos.getCount() > 0) {
		ui->printMessage(to_string(getId()) + "[");
		TruckCargos.print();
		ui->printMessage("]");
	}
	else {
		ui->printMessage("[" + to_string(getId()) + "]");
	}
}

Type NormalTruck::getCargosType() {
	return TruckCargos.peek()->getType();
}


Cargos* NormalTruck::removeFirstCargo() {
	if (TruckCargos.getCount()!=0)
		return TruckCargos.dequeue();
	else return nullptr;
}

bool NormalTruck::isEmpty() {
	return (TruckCargos.getCount()==0);
}

int NormalTruck::getCargosCount() {
	return TruckCargos.getCount();
}
Time NormalTruck::getFirstArrivingCargoTime()
{ 
	if(TruckCargos.peek())
		return TruckCargos.peek()->getCDT();
	else return Time(100000000);
}
void NormalTruck::SetMovingTime(Time t)
{Truck::SetMovingTime(t);
int previousunloadingTime=0;
for(int i=1;i<=TruckCargos.getCount();i++){
	Cargos* cargo=TruckCargos.dequeue();
	
	cargo->setCDT(this->getMovingTime()+(cargo->getDeliveryDistance())/(this->getSpeed())+cargo->getLoadingTime()+previousunloadingTime);
	previousunloadingTime+=cargo->getLoadingTime();
	TruckCargos.enqueue(cargo,-1000*i);

}
}