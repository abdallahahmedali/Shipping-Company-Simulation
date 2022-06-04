#include "Truck.h"
#include "priorityQueue.h"

Truck::Truck() : NextAvailablility(0,0) {
	JourneysMade = 0;
	TruckCounter++;
	TID = TruckCounter;	
	DeliveryInterval = 0;
	isAvailable = true;
	TotalLoadingTime = 0;
	furthestDist = 0;
	TotalActiveTime = 0;
	isLoading = false;
	TDC = 0;
}

int Truck::JourneysMaxNum = 0;
int Truck::TruckCounter = 0;


void Truck::setCapacity(int C) {
	if (C <= 0)
		Capacity = 10; // Default value
	else
		Capacity = C;
}
int Truck::getCapacity() {
	return Capacity;
}

void Truck::setSpeed(int S) {
	if (S <= 0)
		Speed = 10; // Default value
	else
		Speed = S;
}
int Truck::getSpeed() {
	return Speed;
}

void Truck::setIsWorkingNightShifts(bool a) {
	isWorkingNightShifts = a;
}
bool Truck::getIsWorkingNightShifts() {
	return isWorkingNightShifts;
}

int Truck::getJourneysMax() {
	return JourneysMaxNum;
}
void Truck::setJourneysMax(int j) {
	JourneysMaxNum = j;
}
void Truck::incrementJourneysMade() {
	JourneysMade++;
}
int Truck::getJourneysMade() {
	return JourneysMade;
}
float Truck::getDeliveryInterval() {
	return DeliveryInterval;
}


void Truck::setDeliveryInterval(float DI) {
	DeliveryInterval = DI;
}

void Truck::setIsAvailable(bool a) {
	isAvailable = a;
}
bool Truck::getIsAvailable() {
	return isAvailable;
}

void Truck::SetNextAvailability(Time t) {
	NextAvailablility = t;
}
Time Truck::getNextAvailability() const{
	return NextAvailablility;
}

void Truck::setIsLoading(bool a) {
	isLoading = a;
}
bool Truck::getIsLoading() {
	return isLoading;
}
Time Truck::getMovingTime() {
	return MovingTime;
}
void Truck::SetMovingTime(Time t) {

	MovingTime = t;
	
}


void Truck::setTotalActiveTime(int h) {
	TotalActiveTime = h;
}
int Truck::getTotalActiveTime() {
	return TotalActiveTime;
}

int Truck::getTotalLoadingTime()const {
	return TotalLoadingTime;
}
void Truck::setTotalLoadingTime(int LT) {
	TotalLoadingTime = LT;
}
float Truck::getfurthestDistance()const {
	return furthestDist;
}
void Truck::setfurthestDistance(float FD) {
	furthestDist = FD;
}

int Truck::getId() const {
	return TID;
}

int Truck::getTDC() const {
	return TDC;
}

void Truck::incrementTDC() {
	TDC++;
}

void Truck::resetTruck() {
	DeliveryInterval = 0;
	isAvailable = true;
	TotalLoadingTime = 0;
	furthestDist = 0;
	isLoading = false;
}