#include "BuildList.h"

std::vector<Ingredient> buildList::assembleIngredients(std::vector<ChosenMeal> chosenMeals) {
	std::vector<Meal> meals;
	std::vector<Ingredient> ingredients;
	int ingredientIndex = 0;
	for (int i = 0; i < chosenMeals.size(); i++) {
		meals.push_back(foodPlannerData.getMeal(chosenMeals[i].mealName));
	}

	for (int i = 0; i < meals.size(); i++) {
		for (int j = 0; j < meals[i].Ingredients.size(); j++) {
			ingredientIndex = getIngredientIndex(ingredients, meals[i].Ingredients[j]);
			if (ingredientIndex != -1) {
				ingredients[ingredientIndex].Amount = ingredients[ingredientIndex].Amount + meals[i].Ingredients[j].Amount;
			}
			else {
				ingredients.push_back(meals[i].Ingredients[j]);
			}
		}
	}
	return ingredients;
}

int buildList::getIngredientIndex(std::vector<Ingredient> ingredients, Ingredient ingredient) {
	int index = -1;
	for (int i = 0; i < ingredients.size(); i++) {
		if ((ingredients[i].Name == ingredient.Name) && (ingredients[i].Unit == ingredient.Unit)) {
			index = i;
			break;
		}
	}
	return index;
}

std::string buildList::generateStringToPrint(std::vector<Ingredient> ingredients, List listTemplate) {
	std::string ingredientText;
	std::vector<std::string> linesOfText = getLinesOfText(ingredients, listTemplate);
	std::vector<std::string> firstColumn;
	std::vector<std::string> secondColumn;
	for (int i = 0; i < linesOfText.size(); i++) {
		if (i > (linesOfText.size() / 2)) {
			secondColumn.push_back(linesOfText[i]);
		}
		else {
			firstColumn.push_back(linesOfText[i]);
		}
	}
	int firstColumnWidth = getCharsOfBiggestString(firstColumn);
	for (int i = 0; i < secondColumn.size(); i++) {
		ingredientText = ingredientText + firstColumn[i] + getMarginBetweenColumns(firstColumn[i], firstColumnWidth, 4) + secondColumn[i] + '\n';
	}
	if (firstColumn.size() > secondColumn.size()) {
		ingredientText = ingredientText + firstColumn[firstColumn.size() - 1] + '\n';
	}
	return ingredientText;
}

std::vector<Ingredient> buildList::getIngredientsOfCategory(std::vector<Ingredient> ingredients, std::string category) {
	std::vector<Ingredient> ingredientsOfCategory;
	for (int i = 0; i < ingredients.size(); i++) {
		if (ingredients[i].storeCategory == category) {
			ingredientsOfCategory.push_back(ingredients[i]);
		}
	}
	return ingredientsOfCategory;
}

int buildList::getOrderIndex(List list, int order) {
	int index = 0;
	for (int i = 0; i < list.Order.size(); i++) {
		if (list.Order[i] == std::to_string(order)) {
			index = i;
			break;
		}
	}
	return index;
}

std::vector<std::string> buildList::getLinesOfText(std::vector<Ingredient> ingredients, List listTemplate) {
	std::vector<std::string> linesOfText;
	std::vector<Ingredient> ingredientsOfCategory;
	std::vector<std::string> ingredientAmountsAndUnits;
	for (int i = 0; i < ingredients.size(); i++) {
		int decimalPlaces = getDecimalPlaces(ingredients[i].Amount);
		ingredientAmountsAndUnits.push_back(round(ingredients[i].Amount, decimalPlaces) + " " + ingredients[i].Unit);
	}
	int Width = getCharsOfBiggestString(ingredientAmountsAndUnits);
	for (int i = 0; i < listTemplate.Order.size(); i++) {
		std::string storeCategory = listTemplate.IngredientCategories[getOrderIndex(listTemplate, i + 1)];
		ingredientsOfCategory = getIngredientsOfCategory(ingredients, storeCategory);
		if (ingredientsOfCategory.size() != 0) {
			for (int j = 0; j < ingredientsOfCategory.size(); j++) {
				int decimalPlaces = getDecimalPlaces(ingredientsOfCategory[j].Amount);
				std::string line = round(ingredientsOfCategory[j].Amount, decimalPlaces) +  " " + ingredientsOfCategory[j].Unit;
				line = line + getMarginBetweenColumns(line, Width, 2) + ingredientsOfCategory[j].Name;
				linesOfText.push_back(line);
			}
			linesOfText.push_back(" ");
		}
	}
	int amountWidth = getCharsOfBiggestString(linesOfText);
	for (int i = 0; i < linesOfText.size(); i++) {
		
	}
	return linesOfText;
}

int buildList::getCharsOfBiggestString(std::vector<std::string> strings) {
	int mostChars = 0;
	for (int i = 0; i < strings.size(); i++) {
		if (strings[i].length() > mostChars) {
			mostChars = strings[i].length();
		}
	}
	return mostChars;
}

std::string buildList::getMarginBetweenColumns(std::string firstString, int firstColumnWidth, int spacerSize) {
	std::string margin;
	for (int i = 0; i < (firstColumnWidth - firstString.length()) + spacerSize; i++) {
		margin = margin + " ";
	}
	return margin;
}

std::string buildList::round(double num, int decimalPlaces) {
	std::string numStr = std::to_string(num);
	std::string label;
	int endSignal = 0;
	for (int i = 0; i < numStr.length(); i++) {
		label = label + numStr[i];
		if (endSignal) {
			endSignal++;
			if ((endSignal - 1) == decimalPlaces) {
				break;
			}
		}
		if (numStr[i] == '.') {
			endSignal = 1;
			if (decimalPlaces == 0) {
				label.erase(label.size() - 1, 1);
				break;
			}
		}
	}
	return label;
}

int buildList::getDecimalPlaces(double amount) {
	std::string amountString = round(amount, 3);
	int decimalPlaces = 3;
	for (int k = amountString.length() - 1; k >= (amountString.length() - 3); k--) {
		if (amountString[k] != '0') {
			break;
		}
		else {
			decimalPlaces--;
		}
	}
	return decimalPlaces;
}