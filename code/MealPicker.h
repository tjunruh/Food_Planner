#pragma once
#ifndef __MealPicker_H
#define __MealPicker_H
#include "JSON.h"
#include "Calender.h"
#include <ctime>
#include "Food_Planner_Data.h"

class mealPicker {
public:
	std::string pickMeal(std::string category, int ageOrder, monthDayYear date);
	bool findMeal(std::string name, std::vector<std::string> meals);
	std::vector<std::string> deleteName(std::string name, std::vector<std::string> names);
	ChosenMeal getChosenMealOfNthAge(std::vector<ChosenMeal> chosenMeals, int age);
	ChosenMeal getOlderMeal(ChosenMeal meal1, ChosenMeal meal2, int& whichOlder);
	std::vector<ChosenMeal> orderOldestToYoungest(std::vector<ChosenMeal> chosenMeals);
	std::vector<ChosenMeal> deleteChosenMeal(std::vector<ChosenMeal> chosenMeals, monthDayYear currentDate);
};
#endif