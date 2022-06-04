#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int EM, int ID, Time ET) : Event(ID, ET) {
	ExtraMoney = EM;
}

void PromotionEvent::ExecuteEvent(Company* cmp_ptr) {
	// -> Searching for a Normal cargo with specific id to promote it
	Cargos* Cargo = cmp_ptr->HasCargo(getId());

	if (Cargo && Cargo->getType() == NORMAL) {
		// -> Remove the Cargo from the Normal queue
		cmp_ptr->removeCargo(Cargo);

		// -> Promotion of the cargo process
		//		-> 1. Change the type of the cargo
		Cargo->setType(VIP);
		//		-> 2. Add the extra money on the cargo cost
		int CurrCost = Cargo->getCost();
		Cargo->setCost(CurrCost + ExtraMoney);
		//		-> 3. insert the promoted cargo to the VIP list
		cmp_ptr->addCargo(Cargo);
	}

}