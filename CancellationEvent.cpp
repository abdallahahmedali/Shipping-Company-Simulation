#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int ID, Time ET) : Event(ID, ET) {}

void CancellationEvent::ExecuteEvent(Company* cmp_ptr) {

	// -> Searching for a Cargo in waiting list | Returning its address
	Cargos* Cargo = cmp_ptr->HasCargo(getId());

	if (Cargo) {
		// -> Remove the Cargo from the waiting cargo lists
		cmp_ptr->removeCargo(Cargo);

		// -> Adding the cancelled cargo to the cancelled queue
		// cmp_ptr->addCargo(Cargo);
	}
	
}