#include "Calender.h"

monthDayYear calender::getNewDate(monthDayYear currentDate, std::string increaseOrDecrease) {
	int yearDays[12];
	for (int i = 0; i < 12; i++) {
		yearDays[i] = standardYear[i];
	}
	if ((currentDate.year % 4) == 0) {
		yearDays[1] = 29;
		if (((currentDate.year % 100) == 0) && ((currentDate.year % 400) != 0)) {
			yearDays[1] = 28;
		}
	}
	if (increaseOrDecrease == "increase") {
		currentDate = increase(currentDate, yearDays);
	}
	else if (increaseOrDecrease == "decrease") {
		currentDate = decrease(currentDate, yearDays);
	}
	return currentDate;
}
monthDayYear calender::increase(monthDayYear currentDate, int dates[12]) {
	if (currentDate.day != dates[currentDate.month - 1]) {
		currentDate.day = currentDate.day + 1;
	}
	else {
		if (currentDate.month != 12) {
			currentDate.month = currentDate.month + 1;
			currentDate.day = 1;
		}
		else {
			currentDate.year = currentDate.year + 1;
			currentDate.month = 0;
			currentDate.day = 1;
		}
	}
	return currentDate;
}
monthDayYear calender::decrease(monthDayYear currentDate, int dates[12]) {
	if (currentDate.day != 1) {
		currentDate.day = currentDate.day - 1;
	}
	else {
		if (currentDate.month != 1) {
			currentDate.month = currentDate.month - 1;
			currentDate.day = dates[currentDate.month - 1];
		}
		else {
			currentDate.year = currentDate.year - 1;
			currentDate.month = 11;
			currentDate.day = 31;
		}
	}
	return currentDate;
}
monthDayYear calender::getOlderDate(monthDayYear date1, monthDayYear date2, int &indicateWhichOlder) {
	monthDayYear olderDate = date1;
	indicateWhichOlder = 1;
	if (date1.year == date2.year) {
		if (date1.month == date2.month) {
			if (date1.day < date2.day) {
				olderDate = date2;
				indicateWhichOlder = 2;
			}
		}
		else if (date1.month < date2.month) {
			olderDate = date2;
			indicateWhichOlder = 2;
		}
	}
	else if (date1.year < date2.year) {
		olderDate = date2;
		indicateWhichOlder = 2;
	}
	return olderDate;
}