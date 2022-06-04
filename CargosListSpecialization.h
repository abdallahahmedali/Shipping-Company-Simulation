#include "linkedList.h"
#include "Cargos.h"

class CargosListSpecialization {
	Cargos* linkedList::getPtrTo<Cargos*>(int target) {
		QNode<T>* traverser = head;
		while (traverser) {
			if (traverser->getItem() == target)
				return traverser->getItem();
			traverser = traverser->getNext();
		}
		return traverser->getItem();
	}


	bool contains(int data) {
		return getPtrTo(data) != nullptr;
	}
};
