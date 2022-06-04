#pragma once
class Time
{
	int Hour;
	int Day;
public:
	Time() {
		Day = 0;
		Hour = 0;
	}
	int operator -() {
		return -(Day * 24 + Hour);
	}
	Time operator - (Time t) {
		// C = 1:2 -> R = 0:8
		Time t_ret;
		t_ret.Day = Day - t.Day;
		
		if (Hour < t.Hour) {
			t_ret.Day--;
			t_ret.Hour = Hour + 24 - t.Hour;
		}
		else {
			t_ret.Hour = Hour - t.Hour;
		}

		return t_ret;

	}
	template<typename T>
	Time operator + (T hours) {
		// C = 1:2 -> R = 0:8
		Time t_ret(*this);

		if (Hour + hours >= 24) {
			t_ret.Day =this->Day+ (this->Hour + hours) / 24;
			t_ret.Hour = (Hour + (int)hours) % 24;
		}
		else {
			t_ret.Hour = Hour + hours;
			t_ret.Day=Day;
		}

		return t_ret;

	}

	/*Time operator + (Time t)
	{

	Time new_Time;
	new_Time.Day=Day+t.Day+(Hour+t.Hour)/24;
	new_Time.Hour=(Hour+t.Hour)%24;
	return new_Time;
	
	
	}*/
	bool operator > (int i) {
		return (Day * 24 + Hour) > i;
	}
	bool operator > (Time t) {
		return (Day * 24 + Hour) > (t.Day*24+t.Hour);
		
	}
	Time(int d, int h) {
		Day = d;
		Hour = h;
	}
	Time(int hours)
	{
		Day=hours/24;
		Hour=hours%24;
	}
	int getHour() {
		return Hour;
	}
	int getDay() {
		return Day;
	}

	void setHour(int h) {
		if (h >= 0 && h < 24)
			Hour = h;
	}

	void setDay(int d) {
		Day = d;
	}

	void incrementTime(int h = 0, int d = 0) {
		if (h + Hour >= 24) {
			Day += (h + Hour) / 24;
			Hour += (h + Hour + 1) % 24;
		}
		else if (h + Hour < 0) {
			Day += (h + Hour) / 24 - 1;
			Hour += (24 + h) % 24;
		}
		Day += d;
	}


	bool operator == (Time* t) {
		if (this->Hour == t->Hour && this->Day == t->Day)
			return true;
		return false;
	}

	operator int() const
	{
		return Day * 24 + Hour;
	}
};

