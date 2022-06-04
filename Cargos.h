#pragma once
#include<fstream>
#include"Time.h"
#include "TypeEnum.h"

using namespace std;

class Truck; // Forward declaration
class Cargos
{
	Time readyTime;
	int loadingTime;
	float deliveryDistance;
	int Cost;
	bool isDelivered;
	bool isWaitting;
	Time WaitingTime;
	static int MaxW;
	int CID;
	Truck* truckptr;
	Type cargoType;
	Time CDT; //Normal_Cargos.remove()
	
public:
	Cargos();
	~Cargos();

	Cargos(Type t, Time rt, int id, float delDistance, int loading, int c);
	bool operator == (Cargos* c) {
		return (this->CID == c->CID);
	}
	bool operator == (int data) {
		return (this->CID == data);
	}

	void setReadyTime(Time RT);
	void setLoadingTime(int LT);
	void setDeliveryDistance(float D);
	void setCost(int cost);
	void setIsDelivered(bool IsDelivered);
	void setIsWaitting(bool waitting);
	Time getReadyTime()const;
	int getLoadingTime()const;
	float getDeliveryDistance() const;
	float getCost() const;
	bool getIsDelivered() const;
	bool getIsWaitting()const;
	static int getMaxW();
	static void setMaxW(int hours);
	int getCID() const;
	void setCID(int Id);
	void loadCargoData(ifstream& inputFile);
	Truck* getTruck() const;
	void setTruck(Truck* truck);
	Type getType() const;
	void setType(Type t);
	Time getWaittingTime() const;
	void setWaittingTime(Time WT);
	Time getCDT() const;
	void setCDT(Time cargoDT) ;
	
};

