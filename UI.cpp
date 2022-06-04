#include "UI.h"
#include "Event.h"
UI::UI(void)
{
}


UI::~UI(void)
{
}
void UI::printendl()
{
	cout << endl;
}
void UI::printMessage(string text)
{
  cout<<text;
}
string UI::getString()
{
	string text;
	cin >> text;
	return text;
}
int UI::getInteger()
{
	int integer;
	cin >> integer ;
	return integer;

}
void UI::printCurrentTime(Time currTime)
{
	cout << "Current Time (Day:Hour):" << currTime.getDay() << ":" << currTime.getHour() << endl;
}
void UI::printTime(Time time)
{
	cout << time.getDay() << ":" << time.getHour();
}


