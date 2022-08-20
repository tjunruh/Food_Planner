#pragma once

#include "Food_Planner_Data.h"
#include <string>
class buildList {
private:
	std::vector<Ingredient> getIngredientsOfCategory(std::vector<Ingredient> ingredients, std::string category);
	int getOrderIndex(List list, int order);
	std::vector<std::string> getLinesOfText(std::vector<Ingredient> ingredients, List listTemplate);
	int getCharsOfBiggestString(std::vector<std::string> strings);
	std::string getMarginBetweenColumns(std::string firstString, int firstColumnWidth, int spacerSize);
	int getIngredientIndex(std::vector<Ingredient> ingredients, Ingredient ingredient);
	std::string round(double num, int decimalPlaces);
	int getDecimalPlaces(double amount);

public:
	std::vector<Ingredient> assembleIngredients(std::vector<ChosenMeal> chosenMeals);
	std::string generateStringToPrint(std::vector<Ingredient> ingredients, List listTemplate);
	
};