#include "Company.h"
#include "Event.h"
#include "CancellationEvent.h"
#include "ReadyEvent.h"
#include "PromotionEvent.h"
#include "UI.h"
#include <windows.h>
#include <conio.h>

Company::Company() : VIP_Cargos(50), Loading_Trucks(50), Moving_Trucks(50) , Maintenance_Trucks(50), Normal_Trucks(50), Special_Trucks(50), VIP_Trucks(50) {
	MovingCargosCount = 0;
	AutoPCount = 0;
}

Truck* Company::getNextAvailableTruck(enum Type TruckType) {
	Truck* NextAvailableTruck;
	switch (TruckType)
	{
	case VIP:
		NextAvailableTruck = VIP_Trucks.dequeue();
		return NextAvailableTruck;
		break;
	default:
		break;
	}

}

bool Company::addCargo(Cargos* Cargo) {
	float priority = (Cargo->getCost() * Cargo->getDeliveryDistance()) / int(Cargo->getReadyTime());
	switch (Cargo->getType())
	{
	case VIP:
		VIP_Cargos.enqueue(Cargo, priority);
		break;
	case NORMAL:
		Normal_Cargos.insert(Cargo);
		break;
	case SPECIAL:
		Special_Cargos.insert(Cargo);
		break;
	default:
		break;
	}
	return true;
}

bool Company::addCancelledCargo(Cargos* Cargo) {
	Cancelled_Cargos.insert(Cargo);
	return true;
}


Cargos* Company::HasCargo(int id) {
	if (Normal_Cargos.getPtrTo(id))
		return Normal_Cargos.getPtrTo(id);
	else if (Special_Cargos.getPtrTo(id))
		return Special_Cargos.getPtrTo(id);
	return nullptr;
}



bool Company::removeCargo(Cargos* c) {
	// -> Case 1 : The sent cargo is of type VIP
	if (c->getType() == NORMAL)
		Normal_Cargos.remove(c);
	// -> Case 3 : The sent cargo is of type SPECIAL
	else if (c->getType() == SPECIAL)
		Special_Cargos.remove(c);
	else
		return false;
	return true;
}


bool Company::addTruck(Truck* truckPtr,int pri = 1)
{
	if (dynamic_cast<VIPTruck*>(truckPtr)) {
		VIP_Trucks.enqueue(truckPtr, ((1 + 0.001* truckPtr->getSpeed()) / truckPtr->getCapacity())*pri);
		return true;
	}
	else if (dynamic_cast<SpecialTruck*>(truckPtr)) {
		Special_Trucks.enqueue(truckPtr, ((1 + 0.001 * truckPtr->getSpeed()) / truckPtr->getCapacity()) * pri);
		return true;
	}
	else if (dynamic_cast<NormalTruck*>(truckPtr)) {
		Normal_Trucks.enqueue(truckPtr, ((1 + 0.001 * truckPtr->getSpeed()) / truckPtr->getCapacity()) * pri);
		return true;
	}
	else
	{
		return false;
	}
}
void Company::setAutoP(int Days) { AutoP = Days; }
int Company::getAutoP() { return AutoP; }


bool Company::addEvent(Event* e) {
	Events.enqueue(e);
	return true;
}

void Company::ExecuteCurrentEvent() {
	if (!Events.isempty()) {
		Event* e = Events.dequeue();
		e->ExecuteEvent(this);
	}

}

ostream& operator << (ostream& out, Cargos* Cargo) {
	out << Cargo->getCID();
	return out;
}

ostream& operator << (ostream& out, Truck* truck) {
	UI* ui = new UI;
	if (truck)
		truck->print(ui);
	return out;
}

void Company::printWaitingCargos(UI * ui) {

	int w_count = VIP_Cargos.getCount() + Normal_Cargos.getCount() + Special_Cargos.getCount();
	ui->printMessage( to_string( w_count) +" Waiting Cargos: [");
	Normal_Cargos.print();
	ui->printMessage( "]");
	ui->printMessage( " (");
	Special_Cargos.print();
	ui->printMessage( ")");
	ui->printMessage( " {");
	VIP_Cargos.print();
	ui->printMessage( "}");
	ui->printMessage( "\n");

}

void Company::printMovingCargos(UI* ui) {
	ui->printMessage( to_string( MovingCargosCount) +" Moving Cargos: ");
	Moving_Trucks.print();
	ui->printendl();

}

void Company::printLoadingTrucks(UI* ui) {
	int w_count = Loading_Trucks.getCount();
	ui->printMessage( to_string(w_count )+ " Loading Trucks: ");
	Loading_Trucks.print();
    ui->printendl();
}
void Company::printEmptyTrucks(UI* ui) {
	int w_count = Normal_Trucks.getCount() + Special_Trucks.getCount() + VIP_Trucks.getCount();
	ui->printMessage(to_string( w_count) + " Empty Trucks: ");
	Normal_Trucks.print();
	(Normal_Trucks.getCount() > 0) ? ui->printMessage(",") : ui->printMessage("");
	Special_Trucks.print();
	(Special_Trucks.getCount() > 0) ? ui->printMessage(",") : ui->printMessage("");
	VIP_Trucks.print();
	 ui->printendl();
}
void Company::printInCheckUpTrucks(UI * ui) {
	int w_count = Maintenance_Trucks.getCount();
	ui->printMessage( to_string(w_count )+ " In Checkup Trucks: ");
	Maintenance_Trucks.print();
	 ui->printendl();
}
void Company::printDeliveredCargos(UI * ui) {
	int w_count = Delivered_Normal_Cargos.getCount() + Delivered_Special_Cargos.getCount() + Delivered_VIP_Cargos.getCount();
	ui->printMessage(to_string( w_count )+ " Delivered Cargos: ");

	(!Delivered_Normal_Cargos.isempty()) ? ui->printMessage( "[") : ui->printMessage("");
	Delivered_Normal_Cargos.print();
	(!Delivered_Normal_Cargos.isempty()) ? ui->printMessage( "]") : ui->printMessage("");
	(!Delivered_Special_Cargos.isempty())? ui->printMessage("(" ): ui->printMessage("");
	Delivered_Special_Cargos.print();
	(!Delivered_Special_Cargos.isempty()) ? ui->printMessage( ") ") : ui->printMessage("");
	(!Delivered_VIP_Cargos.isempty()) ? ui->printMessage( "{") : ui->printMessage("");
	Delivered_VIP_Cargos.print();
	(!Delivered_VIP_Cargos.isempty()) ? ui->printMessage( "}" ): ui->printMessage("");
	ui->printendl();
}

void Company::NightModeLists() {
	Truck* truck;
	priorityQueue<Truck*> aux_q(50);
	while (VIP_Trucks.getCount() > 0)
	{
		truck = VIP_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}
	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		VIP_Trucks.enqueue(truck, (int)truck->getIsWorkingNightShifts()*((1 + 0.001 * truck->getSpeed()) / (float)truck->getCapacity()));
	}

	while (Normal_Trucks.getCount() > 0)
	{
		truck = Normal_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}
	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		Normal_Trucks.enqueue(truck, (int)truck->getIsWorkingNightShifts() * ((1 + 0.001 * truck->getSpeed()) / (float)truck->getCapacity()));
	}
	while (Special_Trucks.getCount() > 0)
	{
		truck = Special_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}

	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		Special_Trucks.enqueue(truck, (int)truck->getIsWorkingNightShifts() * ((1 + 0.001 * truck->getSpeed()) / (float)truck->getCapacity()));
	}

	
}

void Company::DayModeLists() {
	Truck* truck;
	priorityQueue<Truck*> aux_q(50);
	while (VIP_Trucks.getCount() > 0)
	{
		truck = VIP_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}

	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		VIP_Trucks.enqueue(truck, ((1 + 0.001 * truck->getSpeed()) / truck->getCapacity()));
	}

	while (Normal_Trucks.getCount() > 0)
	{
		truck = Normal_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}
	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		Normal_Trucks.enqueue(truck, ((1 + 0.001 * truck->getSpeed()) / truck->getCapacity()));
	}
	while (Special_Trucks.getCount() > 0)
	{
		truck = Special_Trucks.dequeue();
		aux_q.enqueue(truck, 0);
	}

	while (aux_q.getCount() > 0)
	{
		truck = aux_q.dequeue();
		Special_Trucks.enqueue(truck, ((1 + 0.001 * truck->getSpeed()) / truck->getCapacity()));
	}

}

void Company::simulateProgram(int Mode , UI * ui) {
	// Time Simulation-> Event execution
	system("cls");
	int hours = 24, n = 1;    
	Time* CurrentTime = new Time;
	int countTimeSteps = 0;
	bool normalLoading = false;
	bool specialLoading = false;
	bool vipLoading = false;
	bool isDay = false;

	while (Normal_Cargos.getCount() > 0 || Special_Cargos.getCount() > 0 || VIP_Cargos.getCount() > 0 || Moving_Trucks.getCount() > 0 || Loading_Trucks.getCount() > 0 || Events.getCount() > 0|| Maintenance_Trucks.getCount()>0) // 
	{   
		if(Mode==1)
		{
		getch();
		}
		if(Mode==1||Mode==2)
		{
			system("cls");
		}
		int h, d;
		d = hours / 24;
		h = hours % 24;
		CurrentTime->setDay(d);
		CurrentTime->setHour(h);


		// Arranging trucks according to the shift  5 -> 23 Day Mode {(5),6,7,8,....,23}, Night Mode 0 -> 4 {(0),1,2,3,4}
		if (h == 0) {
			isDay = false;
			NightModeLists();
		}
		else if(h == 5) {
			isDay = true;
			DayModeLists();
		}

		


		// -> Auto-promotion
		// -> Events
		// -> Assignments to trucks

		if (true == true || true || !false) {
			Event* e;
			// -> Execute events
			while (!Events.isempty() && *CurrentTime >= Events.peek()->getEventTime()) {
				e = this->Events.dequeue();
				e->ExecuteEvent(this);
				delete e;
			}

			//##############################################################################################################################################################
			//------------------------------------------------------------ Cargos Auto Promotion ---------------------------------------------------------------------------
			// Function : 
			// Automatically promotes normal cargos if it has been waiting for more the the auto promotion time. 
			//##############################################################################################################################################################


			while (!(Normal_Cargos.isEmpty())) {
				Cargos* cargo = Normal_Cargos.peek();
				if ((*CurrentTime - cargo->getReadyTime()) >= AutoP * 24)
				{
					Event* e = new PromotionEvent(0, cargo->getCID(), *CurrentTime);
					e->ExecuteEvent(this);
					AutoPCount++;
				}
				else {
					break;
				}
			}

			//##############################################################################################################################################################
			//------------------------------------------------------------ Assignment Of Cargos To Trucks ------------------------------------------------------------------
			//##############################################################################################################################################################


			//##############################################################################################################################################################
			//------------------------------------------------------------ Assignment Of VIP Cargos To Trucks --------------------------------------------------------------
			// Function :
			// VIP Cargos are assigned to VIP trucks if they are available.
			// if VIP trucks are not available then they are assigned to Normal or Special Trucks.
			//##############################################################################################################################################################

			while (VIP_Trucks.getCount() > 0 && VIP_Cargos.getCount() >= VIP_Trucks.peek()->getCapacity()&& !vipLoading  && (isDay || VIP_Trucks.peek()->getIsWorkingNightShifts())) {//&& !vipLoading
				Truck* truck = VIP_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(VIP_Cargos.dequeue());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + (truck->getTotalLoadingTime() + truck->getDeliveryInterval()));
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				vipLoading = true;
			}
			//VIP Carogos to Normal Trucks
			while (VIP_Trucks.getCount() == 0 && (Normal_Trucks.getCount() > 0) && VIP_Cargos.getCount() >= Normal_Trucks.peek()->getCapacity() && !vipLoading && (isDay || Normal_Trucks.peek()->getIsWorkingNightShifts())) {
				Truck* truck = Normal_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(VIP_Cargos.dequeue());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + (truck->getTotalLoadingTime() + truck->getDeliveryInterval()));
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				vipLoading = true;
			}
			//VIP Carogos to Speical Trucks
			while (VIP_Trucks.getCount() == 0 && Normal_Trucks.getCount() == 0 && (Special_Trucks.getCount() > 0) && VIP_Cargos.getCount() >= Special_Trucks.peek()->getCapacity() && !vipLoading && (isDay || Special_Trucks.peek()->getIsWorkingNightShifts())) {
				Truck* truck = Special_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(VIP_Cargos.dequeue());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + (truck->getTotalLoadingTime() + truck->getDeliveryInterval()));
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				vipLoading = true;
			}

			//##############################################################################################################################################################
			//------------------------------------------------------------ Assignment Of Special Cargos To Trucks ----------------------------------------------------------
			// Function :
			// Special Cargos are assigned to Special trucks only.
			// if Special trucks are not available then they wait for any special truck to return.
			//##############################################################################################################################################################

			//Special Carogos to Special Trucks
			while ((Special_Trucks.getCount() > 0) && Special_Cargos.getCount() >= Special_Trucks.peek()->getCapacity() && !specialLoading && (isDay || Special_Trucks.peek()->getIsWorkingNightShifts())) {
				Truck* truck = Special_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(Special_Cargos.remove());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + (truck->getTotalLoadingTime() + truck->getDeliveryInterval()));
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				specialLoading = true;
			}

			//##############################################################################################################################################################
			//------------------------------------------------------------ Assignment Of Normal Cargos To Trucks -----------------------------------------------------------
			// Function :
			// Normal Cargos are assigned to Normal trucks if they are available.
			// if Normal trucks are not available then they are assigned to VIP Trucks.
			//##############################################################################################################################################################

			///assign normal cargo to normal truck
			while ((Normal_Trucks.getCount() > 0) && Normal_Cargos.getCount() >= Normal_Trucks.peek()->getCapacity() && !normalLoading && (isDay || Normal_Trucks.peek()->getIsWorkingNightShifts())) {
				Truck* truck = Normal_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(Normal_Cargos.remove());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + (truck->getTotalLoadingTime() + truck->getDeliveryInterval()));
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				normalLoading = true;
			}
			// Normal -> VIP 
			while (Normal_Trucks.getCount() == 0 && (VIP_Trucks.getCount() > 0) && Normal_Cargos.getCount() >= VIP_Trucks.peek()->getCapacity() && !normalLoading && (isDay || VIP_Trucks.peek()->getIsWorkingNightShifts())) {
				Truck* truck = VIP_Trucks.dequeue();
				for (int i = 0; i < truck->getCapacity(); i++)
				{
					truck->addCargo(Normal_Cargos.remove());
				}
				truck->setIsAvailable(false);
				truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
				truck->setIsLoading(true);
				truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
				Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				normalLoading = true;
			}

			//##############################################################################################################################################################
			//------------------------------------------------------------ Maximum Time -------------------------------------------------------------
			// Function :
			// Checks if any Non-VIP Cargos have been waiting for more than the maximum wait time.
			// If they are then they are immediatley assigned to any suitable truck that's available and start their delivery.
			//##############################################################################################################################################################
			while (Normal_Cargos.peek() && (*CurrentTime - Normal_Cargos.peek()->getReadyTime()) >= Cargos::getMaxW() )
			{
				int extraJ = (Maintenance_Trucks.peek()) ? Maintenance_Trucks.peek()->getJourneysMade() % Maintenance_Trucks.peek()->getJourneysMax() : 0;
				if (Normal_Trucks.getCount() > 0 && (isDay || Normal_Trucks.peek()->getIsWorkingNightShifts()))
				{
					Cargos* cargo = Normal_Cargos.remove();
					Truck* truck = Normal_Trucks.dequeue();
					truck->setTotalLoadingTime(0);
					truck->addCargo(cargo);
					truck->setIsAvailable(false);
					truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
					truck->setIsLoading(true);
					truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
					Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				}
				else if (VIP_Trucks.getCount() > 0 && (isDay || VIP_Trucks.peek()->getIsWorkingNightShifts()))
				{
					Cargos* cargo = Normal_Cargos.remove();
					Truck* truck = VIP_Trucks.dequeue();
					truck->setTotalLoadingTime(0);
					truck->addCargo(cargo);
					truck->setIsAvailable(false);
					truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
					truck->setIsLoading(true);
					truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
					Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				}
				else if (Maintenance_Trucks.getCount() > 0 && extraJ != 0 && (isDay || Maintenance_Trucks.peek()->getIsWorkingNightShifts())) {
					Cargos* cargo = Normal_Cargos.remove();
					Truck* truck = Maintenance_Trucks.dequeue();
					truck->setSpeed(0.5*truck->getSpeed());
					truck->setTotalLoadingTime(0);
					truck->addCargo(cargo);
					truck->setIsAvailable(false);
					truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
					truck->setIsLoading(true);
					truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
					Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				}
				else
					break;
			}

			///checking for Special Cargos that have been waitting  for MawW or greater
			while (Special_Cargos.peek() && (*CurrentTime - Special_Cargos.peek()->getReadyTime()) >= Cargos::getMaxW())
			{
				int extraJ = (Maintenance_Trucks.peek())?Maintenance_Trucks.peek()->getJourneysMade() % Maintenance_Trucks.peek()->getJourneysMax() : 0;
				if (Special_Trucks.getCount() > 0 && (isDay || Special_Trucks.peek()->getIsWorkingNightShifts()))
				{
					Cargos* cargo = Special_Cargos.remove();
					Truck* truck = Special_Trucks.dequeue();
					truck->setTotalLoadingTime(0);
					truck->addCargo(cargo);
					truck->setIsAvailable(false);
					truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
					truck->setIsLoading(true);
					truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
					Loading_Trucks.enqueue(truck, -truck->getMovingTime());

				}
				else if (Maintenance_Trucks.getCount() > 0 && extraJ !=0 && dynamic_cast<SpecialTruck*>(Maintenance_Trucks.peek()) && (isDay || Maintenance_Trucks.peek()->getIsWorkingNightShifts())) {
					Cargos* cargo = Special_Cargos.remove();
					Truck* truck = Maintenance_Trucks.dequeue();
					truck->setSpeed(0.5 * truck->getSpeed());
					truck->setTotalLoadingTime(0);
					truck->addCargo(cargo);
					truck->setIsAvailable(false);
					truck->SetNextAvailability(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime());
					truck->setIsLoading(true);
					truck->SetMovingTime(*CurrentTime + (truck->getTotalLoadingTime()));
					Loading_Trucks.enqueue(truck, -truck->getMovingTime());
				}
				else
					break;

			}



			// -> Maintenance
			// -> loading -> moving -> waiting

			//##############################################################################################################################################################
			//------------------------------------------------------------ Changing Truck State From [Loading] => [Moving] -------------------------------------------------
			//##############################################################################################################################################################

			Truck* truck;
			Cargos* cargo;
			while (Loading_Trucks.peek() && !(Loading_Trucks.peek()->getMovingTime() > *CurrentTime)) {
				truck = Loading_Trucks.dequeue();
				double Prob = ((double)rand()) / RAND_MAX; //1
				if (truck->getCargosType() == VIP) vipLoading = false;
				else if (truck->getCargosType() == SPECIAL) specialLoading = false;
				else normalLoading = false;
				if (Prob <= 0.1) {
					while (truck->getCargosCount() > 0)
					{
						cargo = truck->removeFirstCargo();
						addCargo(cargo);
					}
					truck->resetTruck(); //reseting the loading time of the truck
					if (dynamic_cast<VIPTruck*>(truck)) {
						Maintenance_Trucks.enqueue(truck, -(*CurrentTime + VIPTruck::getCheckup()));
						truck->SetNextAvailability(*CurrentTime + VIPTruck::getCheckup());
					}
					else if (dynamic_cast<SpecialTruck*>(truck)) {
						Maintenance_Trucks.enqueue(truck, -(*CurrentTime + SpecialTruck::getCheckup()));
						truck->SetNextAvailability(*CurrentTime + SpecialTruck::getCheckup());
					}
					else if (dynamic_cast<NormalTruck*>(truck)) {
						Maintenance_Trucks.enqueue(truck, -(*CurrentTime + NormalTruck::getCheckup()));
						truck->SetNextAvailability(*CurrentTime + NormalTruck::getCheckup());
					}
				}
				else {
					//Moving_Trucks.enqueue(truck, -(*CurrentTime + truck->getDeliveryInterval() + truck->getTotalLoadingTime()));
					Moving_Trucks.enqueue(truck, -((truck->getFirstArrivingCargoTime()))+0.1);
					MovingCargosCount += truck->getCargosCount();
				}

			}
		}
		//##############################################################################################################################################################
		//------------------------------------------------------------ Changing Truck State From [Check-Up] => [Waiting] -----------------------------------------------
		//##############################################################################################################################################################

		while (Maintenance_Trucks.peek() && !(Maintenance_Trucks.peek()->getNextAvailability() > *CurrentTime))
		{
			Truck* truck = Maintenance_Trucks.dequeue();
			addTruck(truck);
		}

		//##############################################################################################################################################################
		//------------------------------------------------------------ Cargo Delivery Logic ----------------------------------------------------------------------------
		//##############################################################################################################################################################
		Truck* truck;

		while (Moving_Trucks.peek() &&!( Moving_Trucks.peek()->getFirstArrivingCargoTime()>*CurrentTime))
		{   
			truck = Moving_Trucks.dequeue();
			truck->incrementTDC();
			Cargos* c=truck->removeFirstCargo(); ////there some changes must be made
			c->setWaittingTime(truck->getMovingTime()-c->getReadyTime());  ///seting the waiting time of the cargo till the truck moved
			if(c->getType()==VIP){Delivered_VIP_Cargos.enqueue(c); }
			else if(c->getType()==SPECIAL){Delivered_Special_Cargos.enqueue(c);}
			else if(c->getType()==NORMAL){Delivered_Normal_Cargos.enqueue(c);}
			MovingCargosCount--;
			int Speed = 0;
			float DI = truck->getDeliveryInterval();
			float FD = truck->getfurthestDistance();
			if(truck->getCargosCount()==0)
			{
				Moving_Trucks.enqueue(truck, -(*CurrentTime + truck->getfurthestDistance() / truck->getSpeed()));
				Speed = truck->getSpeed();
				truck->setTotalActiveTime(truck->getTotalActiveTime() + (DI - (FD / Speed)) + truck->getTotalLoadingTime());
				
			}
			else 
				Moving_Trucks.enqueue(truck,-((truck->getFirstArrivingCargoTime()))+0.1);
		}

		//##############################################################################################################################################################
		//------------------------------------------------------------ Changing Truck State From [Moving] => [Check-Up/Waiting] ----------------------------------------
		//##############################################################################################################################################################

		while (Moving_Trucks.peek() && !(Moving_Trucks.peek()->getNextAvailability() > *CurrentTime)) {
			truck = Moving_Trucks.dequeue();
			truck->incrementJourneysMade(); //increaseing the journeys counter of the truck
			truck->resetTruck(); //reseting the loading time of the truck

			if (truck->getJourneysMade() % Truck::getJourneysMax() != 0) {
				addTruck(truck);
			}
			else
			{
				if (dynamic_cast<VIPTruck*>(truck)) {
					Maintenance_Trucks.enqueue(truck, -(*CurrentTime + VIPTruck::getCheckup()));
					truck->SetNextAvailability(*CurrentTime + VIPTruck::getCheckup());
				}
				else if (dynamic_cast<SpecialTruck*>(truck)) {
					Maintenance_Trucks.enqueue(truck, -(*CurrentTime + SpecialTruck::getCheckup()));
					truck->SetNextAvailability(*CurrentTime + SpecialTruck::getCheckup());
				}
				else if (dynamic_cast<NormalTruck*>(truck)) {
					Maintenance_Trucks.enqueue(truck, -(*CurrentTime + NormalTruck::getCheckup()));
					truck->SetNextAvailability(*CurrentTime + NormalTruck::getCheckup());
				}
			}
		}
	
		if(Mode==1||Mode==2)
		{ // we must use ui  here instead of  cout down here////
			ui->printMessage( "Current Time (Day:Hour) " + to_string( CurrentTime->getDay()) + ":" + to_string(CurrentTime->getHour()) +"\n" );
			this->printWaitingCargos(ui);
			ui->printMessage( "------------------------------------------------------\n");
			this->printLoadingTrucks(ui);
			ui->printMessage( "------------------------------------------------------\n");
			this->printEmptyTrucks(ui);
			ui->printMessage( "------------------------------------------------------\n");
			this->printMovingCargos(ui);
			ui->printMessage( "------------------------------------------------------\n");
			this->printInCheckUpTrucks(ui);
			ui->printMessage( "------------------------------------------------------\n");
			this->printDeliveredCargos(ui);
			ui->printMessage( "------------------------------------------------------\n");
		}
		
		if(Mode==2)
		{
			Sleep(1000);
		}
	 
	  hours++;
	 }


}

void Company::printOutputFile(UI * ui)
{
	
	int totalWaitingTime = 0; float totalActiveTime = 0; float utilization = 0;
	int numOfNormalCargos=Delivered_Normal_Cargos.getCount()+AutoPCount; /// this is the sum of all Normal Cargos includeing the promoted on
	int totalNumberOfDeliveredCargos=Delivered_Normal_Cargos.getCount()+Delivered_Special_Cargos.getCount()+Delivered_VIP_Cargos.getCount();
	int totalNumberOfTrucks = Normal_Trucks.getCount() + Special_Trucks.getCount() + VIP_Trucks.getCount();
	ofstream outputfile("output.txt", ios::out);
	
	if(!outputfile.is_open())
	{
		ui->printMessage("error ??????????????????????\n");  
		return;
	}
	priorityQueue <Cargos*> deliveredCargos(totalNumberOfDeliveredCargos);

	for(int i=0;i<Delivered_Normal_Cargos.getCount();i++)
	{   
		Cargos* c=Delivered_Normal_Cargos.dequeue();
		totalWaitingTime+=int(c->getWaittingTime());
		deliveredCargos.enqueue(c,-(c->getCDT()));
		Delivered_Normal_Cargos.enqueue(c);
	}

	for(int i=0;i<Delivered_Special_Cargos.getCount();i++)
	{  
		Cargos* c=Delivered_Special_Cargos.dequeue();
		totalWaitingTime+=int(c->getWaittingTime());
		deliveredCargos.enqueue(c,-(c->getCDT()));
		Delivered_Special_Cargos.enqueue(c);
	}

	for(int i=0;i<Delivered_VIP_Cargos.getCount();i++)
	{  
		Cargos* c=Delivered_VIP_Cargos.dequeue();
		totalWaitingTime+=int(c->getWaittingTime());
		deliveredCargos.enqueue(c,-(c->getCDT()));
		Delivered_VIP_Cargos.enqueue(c);
	}

	outputfile << "CDT" << "\tID" << "\tPT" << "\tWT" << "\tTID" << endl;
	Time SimEndTime;
	for (int i = 0; i < totalNumberOfDeliveredCargos; i++)
	{
		Cargos* c = deliveredCargos.dequeue();
		Truck* T = c->getTruck();
		outputfile << (c->getCDT()).getDay() << ":" << c->getCDT().getHour();
		outputfile << "\t" << (c->getCID()) << "\t";
		outputfile << (c->getReadyTime()).getDay() << ":" << c->getReadyTime().getHour() << "\t";
		outputfile << (c->getWaittingTime()).getDay() << ":" << c->getWaittingTime().getHour() << "\t";
		outputfile << T->getId() << endl;
		SimEndTime = T->getNextAvailability();
	}

	for (int i = 0; i < Normal_Trucks.getCount(); i++)
	{
		Truck* t = Normal_Trucks.dequeue();
		totalActiveTime += int(t->getTotalActiveTime());
		utilization += (t->getJourneysMade() > 0) ? (t->getTDC() / (float)(t->getCapacity() * t->getJourneysMade())) * (t->getTotalActiveTime() / (float)int(SimEndTime)) : 0;
		addTruck(t,INT_MIN);
	}

	for (int i = 0; i < Special_Trucks.getCount(); i++)
	{
		Truck* t = Special_Trucks.dequeue();
		totalActiveTime += int(t->getTotalActiveTime());
		utilization += (t->getJourneysMade() > 0)?(t->getTDC() / (float)(t->getCapacity() * t->getJourneysMade())) * (t->getTotalActiveTime() / (float)int(SimEndTime)) : 0;
		addTruck(t,INT_MIN);
	}

	for (int i = 0; i < VIP_Trucks.getCount(); i++)
	{
		Truck* t = VIP_Trucks.dequeue();
		totalActiveTime += int(t->getTotalActiveTime());
		utilization += (t->getJourneysMade() > 0) ? (t->getTDC() / (float)(t->getCapacity() * t->getJourneysMade())) * (t->getTotalActiveTime() / (float)int(SimEndTime)) : 0;
		addTruck(t,INT_MIN);
	}

	

	int days=(totalWaitingTime/totalNumberOfDeliveredCargos)/24; int hours=(totalWaitingTime/totalNumberOfDeliveredCargos)%24;
	outputfile<<"Cargos : "<<totalNumberOfDeliveredCargos<<"[N: "<<Delivered_Normal_Cargos.getCount()<<", S: "<<Delivered_Special_Cargos.getCount()<<", V: "<<Delivered_VIP_Cargos.getCount()<<"]"<<endl;
	outputfile<<"Cargo Avg Wait = "<<days<<":"<<hours << endl;
	int autoPPerc = (totalNumberOfDeliveredCargos > 0) ? (float(AutoPCount) / numOfNormalCargos) * 100 : 0;
	outputfile << "Auto-promoted Cargos: " << autoPPerc << "%" << endl;
	outputfile << "Trucks: " << totalNumberOfTrucks << "[N: " << Normal_Trucks.getCount() << ", S: " << Special_Trucks.getCount() << ", V: " << VIP_Trucks.getCount() << "]" << endl;
	outputfile << "Avg Active time = " << ((totalActiveTime/totalNumberOfTrucks)/int(SimEndTime))*100 << "%" << endl;
	outputfile << "Avg utilization = " << (utilization/totalNumberOfTrucks) * 100 << "%" << endl; //  tDC/(TC*N) * (tAT/TSim) 



}


bool Company::readInputFile(UI* ui)
{
	ui->printMessage("please enter the input file name\n");
	string fileName = ui->getString();
	ifstream inputFile(fileName, ios::in);
	if (inputFile.is_open() == false)
	{
		ui->printMessage("the entered file name is wrong!!!!!");
		return false;
	}
	int noOfNormalTrucks, noOfVIPTrucks, noOfSpecialTrucks;
	inputFile >> noOfNormalTrucks >> noOfSpecialTrucks >> noOfVIPTrucks;/////the first line of the input file that contains the number of each truck type//

	int TruckSpeed;


	int TruckCap;
	bool nightShifts;




	Truck* truckPtr;
	for (int i = 0; i < noOfNormalTrucks; i++)
	{
		inputFile >> TruckSpeed >> TruckCap >> nightShifts;
		truckPtr = new NormalTruck(TruckSpeed, TruckCap, nightShifts);
		this->addTruck(truckPtr);
	}

	for (int i = 0; i < noOfSpecialTrucks; i++)
	{
		inputFile >> TruckSpeed >> TruckCap >> nightShifts;
		truckPtr = new SpecialTruck(TruckSpeed, TruckCap, nightShifts);
		this->addTruck(truckPtr);
	}
	for (int i = 0; i < noOfVIPTrucks; i++)
	{
		inputFile >> TruckSpeed >> TruckCap >> nightShifts;
		truckPtr = new VIPTruck(TruckSpeed, TruckCap, nightShifts);
		this->addTruck(truckPtr);
	}

	int normalTruckCheckupDurations, specialTruckCheckupDurations, vipTruckCheckupDurations, noOfJourneys;
	inputFile >> noOfJourneys >> normalTruckCheckupDurations >> specialTruckCheckupDurations >> vipTruckCheckupDurations;
	Truck::setJourneysMax(noOfJourneys);
	NormalTruck::setCheckup(normalTruckCheckupDurations);
	SpecialTruck::setCheckup(specialTruckCheckupDurations);
	VIPTruck::setCheckup(vipTruckCheckupDurations);


	int MaxW, AutoP;
	inputFile >> AutoP >> MaxW;
	this->setAutoP(AutoP);
	Cargos::setMaxW(MaxW);


	int noOfEvents;
	inputFile >> noOfEvents;
	for (int i = 0; i < noOfEvents; i++)
	{
		char eventType;
		inputFile >> eventType;
		switch (eventType)
		{
		case 'R':
		{ char cargoType;
		inputFile >> cargoType;

		Type type;
		if (cargoType == 'N') type = NORMAL;
		else if (cargoType == 'S')  type = SPECIAL;
		else if (cargoType == 'V') type = VIP;
		int Days, Hours, Id, cost, LT;   char temp;
		float dist;
		inputFile >> Days >> temp >> Hours >> Id >> dist >> LT >> cost;
		Time ET; ET.setDay(Days);
		ET.setHour(Hours);
		Event* readyEvent = new ReadyEvent(type, dist, LT, cost, Id, ET);
		this->addEvent(readyEvent);
		break;

		}


		case 'X':
		{int Days, Hours, ID;
		char temp;
		inputFile >> Days >> temp >> Hours >> ID;
		Time ET; ET.setDay(Days);
		ET.setHour(Hours);
		Event* cancellationEvent = new CancellationEvent(ID, ET);

		this->addEvent(cancellationEvent);
		break;

		}

		case 'P': {
			int Days, Hours, ID, price;
			char temp;
			inputFile >> Days >> temp >> Hours >> ID >> price;
			Time ET; ET.setDay(Days);
			ET.setHour(Hours);
			Event* promotionEvent = new PromotionEvent(price, ID, ET);
			this->addEvent(promotionEvent);
			break;

		}
		default:
			break;
		}

	}
}

Company::~Company() {
	while (!Normal_Cargos.isEmpty())
		delete Normal_Cargos.remove();

	while (!Special_Cargos.isEmpty())
		delete Special_Cargos.remove();

	while (!Cancelled_Cargos.isEmpty())
		delete Cancelled_Cargos.remove();

	while (!Delivered_Normal_Cargos.isempty())
		delete Delivered_Normal_Cargos.dequeue();

	while (!Delivered_Special_Cargos.isempty())
		delete Delivered_Special_Cargos.dequeue();

	while (!Delivered_VIP_Cargos.isempty())
		delete Delivered_VIP_Cargos.dequeue();

	while (!Events.isempty())
		delete Events.dequeue();

	while (VIP_Cargos.getCount() != 0)
		delete VIP_Cargos.dequeue();

	while (VIP_Trucks.getCount() != 0)
		delete VIP_Trucks.dequeue();

	while (Normal_Trucks.getCount() != 0)
		delete Normal_Trucks.dequeue();

	while (Special_Trucks.getCount() != 0)
		delete Special_Trucks.dequeue();

	while (Moving_Trucks.getCount() != 0)
		delete Moving_Trucks.dequeue();

	while (Loading_Trucks.getCount() != 0)
		delete Loading_Trucks.dequeue();

	while (Maintenance_Trucks.getCount() != 0)
		delete Maintenance_Trucks.dequeue();
}