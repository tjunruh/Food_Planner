#include "MealPicker.h"

std::string mealPicker::pickMeal(std::string category, int ageOrder, monthDayYear date) {
	std::string oldestMealName = "";
	ChosenMeal chosenMeal;
	std::vector<std::string> existingMealOfCategory;
	std::vector<ChosenMeal> chosenMealOfCategory;
	std::vector<Meal> meals = foodPlannerData.getMeals();
	std::vector<ChosenMeal> chosenMeals = foodPlannerData.getChosenMeals();
	chosenMeals = deleteChosenMeal(chosenMeals, date);
	chosenMeals = orderOldestToYoungest(chosenMeals);
	monthDayYear oldestDate;
	oldestDate.year = 0;
	oldestDate.month = 0;
	oldestDate.day = 0;
	for (int i = 0; i < meals.size(); i++) {
		for (int j = 0; j < meals[i].Categories.size(); j++) {
			if (meals[i].Categories[j] == category) {
				existingMealOfCategory.push_back(meals[i].Name);
			}
		}
	}
	for (int i = (chosenMeals.size() - 1); i >= 0; i--) {
		if (findMeal(chosenMeals[i].mealName, existingMealOfCategory)) {
			chosenMealOfCategory.push_back(chosenMeals[i]);
			existingMealOfCategory = deleteName(chosenMeals[i].mealName, existingMealOfCategory);
		}
	}
	if (existingMealOfCategory.size() != 0) {
		//srand((unsigned) time(NULL));
		if (ageOrder < existingMealOfCategory.size()) {
			oldestMealName = existingMealOfCategory[ageOrder];
		}
		else {
			if (chosenMealOfCategory.size() != 0) {
				chosenMeal = getChosenMealOfNthAge(chosenMealOfCategory, (ageOrder - existingMealOfCategory.size()));
				oldestMealName = chosenMeal.mealName;
			}
		}
		
	}
	else if (chosenMealOfCategory.size() != 0) {
		chosenMeal = getChosenMealOfNthAge(chosenMealOfCategory, ageOrder);
		oldestMealName = chosenMeal.mealName;
	}
	return oldestMealName;
}

bool mealPicker::findMeal(std::string name, std::vector<std::string> meals) {
	bool found = false;
	for (int i = 0; i < meals.size(); i++) {
		if (meals[i] == name) {
			found = true;
			break;
		}
	}
	return found;
}

std::vector<std::string> mealPicker::deleteName(std::string name, std::vector<std::string> names) {
	for (int i = 0; i < names.size(); i++) {
		if (names[i] == name) {
			names.erase(names.begin() + i);
			break;
		}
	}
	return names;
}

ChosenMeal mealPicker::getChosenMealOfNthAge(std::vector<ChosenMeal> chosenMeals, int age) {
	ChosenMeal NthAgedChosenMeal;
	//while (((float)age / ((float)chosenMeals.size() - 1)) > 1) {
	//	age = age - chosenMeals.size();
	//}
	std::vector<ChosenMeal> orderedChosenMeals = orderOldestToYoungest(chosenMeals);
	if (age < orderedChosenMeals.size()) {
		NthAgedChosenMeal = orderedChosenMeals[age];
	}
	else {
		NthAgedChosenMeal = orderedChosenMeals[orderedChosenMeals.size() - 1];
	}
	return NthAgedChosenMeal;
}

ChosenMeal mealPicker::getOlderMeal(ChosenMeal meal1, ChosenMeal meal2, int& whichOlder) {
	ChosenMeal olderMeal = meal1;
	whichOlder = 1;
	if (meal1.date.year == meal2.date.year) {
		if (meal1.date.month == meal2.date.month) {
			if (meal1.date.day > meal2.date.day) {
				olderMeal = meal2;
				whichOlder = 2;
			}
		}
		else if (meal1.date.month > meal2.date.month) {
			olderMeal = meal2;
			whichOlder = 2;
		}
	}
	else if (meal1.date.year > meal2.date.year) {
		olderMeal = meal2;
		whichOlder = 2;
	}
	return olderMeal;
}



std::vector<ChosenMeal> mealPicker::orderOldestToYoungest(std::vector<ChosenMeal> chosenMeals) {
	ChosenMeal oldestMeal;
	std::vector<ChosenMeal> orderedChosenMeals;
	int index = 0;
	int whichOlder = 0;
	int elements = chosenMeals.size();
	calender dateHandler;
	for (int i = 0; i < elements; i++) {
		oldestMeal = chosenMeals[0];
		index = 0;
		for (int j = 0; j < chosenMeals.size(); j++) {
			oldestMeal = getOlderMeal(oldestMeal, chosenMeals[j], whichOlder);
			if (whichOlder == 2) {
				index = j;
			}
		}
		chosenMeals.erase(chosenMeals.begin() + index);
		orderedChosenMeals.push_back(oldestMeal);
	}
	return orderedChosenMeals;
}

std::vector<ChosenMeal> mealPicker::deleteChosenMeal(std::vector<ChosenMeal> chosenMeals, monthDayYear currentDate) {
	for (int i = 0; i < chosenMeals.size(); i++) {
		if ((chosenMeals[i].date.day == currentDate.day) && (chosenMeals[i].date.month == currentDate.month) && (chosenMeals[i].date.year == currentDate.year)) {
			chosenMeals.erase(chosenMeals.begin() + i);
			break;
		}
	}
	return chosenMeals;
}