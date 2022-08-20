#pragma once
#ifndef __Calender_H
#define __Calender_H

#include <string>

struct monthDayYear {
	int month;
	int day;
	int year;
};
class calender {
	
private:
	int standardYear[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	monthDayYear decrease(monthDayYear currentDate, int dates[12]);
	monthDayYear increase(monthDayYear currentDate, int dates[12]);
public:
	monthDayYear getNewDate(monthDayYear currentDate, std::string increaseOrDecrease);
	monthDayYear getOlderDate(monthDayYear date1, monthDayYear date2, int &indicateWhichOlder);
};
#endif