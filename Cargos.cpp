#pragma once
#include "Cargos.h"

int Cargos::MaxW = 0;

Cargos::Cargos(void) 
{
	isDelivered = false;
	isWaitting = false;
	
}

Cargos::Cargos(enum Type t, Time rt, int id, float delDistance, int loading, int c)
{
	isDelivered = false;
	isWaitting = false;
	truckptr=nullptr;
	cargoType = t;
	readyTime = rt;
	CID = id;
	deliveryDistance = delDistance;
	loadingTime = loading;
	Cost = c;
}	


Cargos::~Cargos(void)
{
}

void Cargos::setReadyTime(Time RT)
{
	readyTime = RT;
}
void Cargos::setLoadingTime(int LT)
{
	loadingTime = LT;
}
void Cargos::setDeliveryDistance(float D)
{
	deliveryDistance = 0;
	if (D > 0)
		deliveryDistance = D;
}
void Cargos::setCost(int cost)
{
	Cost = 0;
	if (cost > 0)
		Cost = cost;
}
void Cargos::setIsDelivered(bool IsDelivered)
{
	isDelivered = IsDelivered;
}
void Cargos::setIsWaitting(bool waitting)
{
	isWaitting = waitting;
}
Time Cargos::getReadyTime()const
{
	return readyTime;
}
int Cargos::getLoadingTime()const
{
	return loadingTime;
}
float Cargos::getDeliveryDistance() const
{
	return deliveryDistance;
}
float Cargos::getCost() const
{
	return Cost;
}
bool Cargos::getIsDelivered() const
{
	return isDelivered;
}
bool Cargos::getIsWaitting()const
{
	return isWaitting;
}
int Cargos::getMaxW()
{
	return MaxW;
}
void Cargos::setMaxW(int hours)
{
	if (hours > 0)
	{
		MaxW = hours;

	}

}
int Cargos::getCID() const
{
	return CID;
}
void Cargos::setCID(int Id)
{
	CID = Id;
}

Truck* Cargos::getTruck() const {
	return truckptr;
}
void Cargos::setTruck(Truck* truck) {
	truckptr = truck;
}

Type Cargos::getType() const {
	return cargoType;
}
void Cargos::setType(Type t) {
	cargoType = t;
}
Time Cargos::getWaittingTime() const
{  
	return WaitingTime; 
}
void Cargos::setWaittingTime(Time WT)
{ 
	WaitingTime=WT;
}
Time Cargos::getCDT() const
{
	return CDT;
}
void Cargos::setCDT(Time cargoDT)
{
	CDT=cargoDT;
}
