#pragma once
#include <string>
#include <iostream>
#include "Time.h"


using namespace std;

class UI
{

public:

	UI(void);
	void printendl();
	void printMessage(string text);
	string getString();
	int getInteger();
	void printCurrentTime(Time currTime);
	void printTime(Time time);
	
	~UI(void);

};

