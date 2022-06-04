#pragma once
#include "Event.h"

Event::Event(int ID, Time ET) {
	Id = ID;
	EventTime = ET;
}

Time Event::getEventTime() const {
	return EventTime;
}

void Event::setEventTime(Time t) {
	EventTime = t;
}

int Event::getId() const {
	return Id;
}
void Event::setId(int i) {
	Id = i;
}