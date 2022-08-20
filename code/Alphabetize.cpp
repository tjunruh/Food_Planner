#include "Alphabetize.h"

alphabetize labelOrganizer;

std::vector<wxString> alphabetize::alphabetizeVector(std::vector<wxString> labels) {
	std::vector<wxString> organizedStrings;
	int elements = labels.size();
	for (int i = 0; i < elements; i++) {
		for (int j = 0; j < labels.size(); j++) {
			if (isHighestAlphabetical(labels, labels[j])) {
				organizedStrings.push_back(labels[j]);
				labels.erase(labels.begin() + j);
				break;
			}
		}
	}
	return organizedStrings;
}

std::vector<std::string> alphabetize::alphabetizeVector(std::vector<std::string> labels) {
	std::vector <std::string> organizedStrings;
	int elements = labels.size();
	for (int i = 0; i < elements; i++) {
		for (int j = 0; j < labels.size(); j++) {
			if (isHighestAlphabetical(labels, labels[j])) {
				organizedStrings.push_back(labels[j]);
				labels.erase(labels.begin() + j);
				break;
			}
		}
	}
	return organizedStrings;
}

std::vector<Ingredient> alphabetize::alphabetizeVector(std::vector<Ingredient> ingredients) {
	std::vector<Ingredient> organizedIngredients;
	int elements = ingredients.size();
	for (int i = 0; i < elements; i++) {
		for (int j = 0; j < ingredients.size(); j++) {
			if (isHighestAlphabetical(ingredients, ingredients[j])) {
				organizedIngredients.push_back(ingredients[j]);
				ingredients.erase(ingredients.begin() + j);
				break;
			}
		}
	}
	return organizedIngredients;
}

bool alphabetize::isHighestAlphabetical(std::vector<wxString> labels, wxString label) {
	bool isHighest = true;
	for (int i = 0; i < labels.size(); i++) {
		if (toLowerString(label) > toLowerString(labels[i])) {
			isHighest = false;
			break;
		}
	}
	return isHighest;
}

bool alphabetize::isHighestAlphabetical(std::vector<std::string> labels, std::string label) {
	bool isHighest = true;
	for (int i = 0; i < labels.size(); i++) {
		if (toLowerString(label) > toLowerString(labels[i])) {
			isHighest = false;
			break;
		}
	}
	return isHighest;
}

bool alphabetize::isHighestAlphabetical(std::vector<Ingredient> ingredients, Ingredient ingredient) {
	bool isHighest = true;
	for (int i = 0; i < ingredients.size(); i++) {
		if (toLowerString(ingredient.Name) > toLowerString(ingredients[i].Name)) {
			isHighest = false;
			break;
		}
	}
	return isHighest;
}
int alphabetize::positionToInsert(std::vector<std::string> labels, std::string label) {
	int index = 0;
	for (int i = 0; i < labels.size(); i++) {
		if (toLowerString(label) < toLowerString(labels[i])) {
			index = i;
			break;
		}
		if (i == (labels.size() - 1)) {
			index = i + 1;
		}
	}
	return index;
}

std::string alphabetize::toLowerString(std::string str) {
	std::string lowerCaseString;
	char ch;
	for (int i = 0; i < str.length(); i++) {
		ch = tolower(str[i]);
		lowerCaseString = lowerCaseString + ch;
	}
	return lowerCaseString;
}

wxString alphabetize::toLowerString(wxString str) {
	wxString lowerCaseString;
	char ch;
	for (int i = 0; i < str.length(); i++) {
		ch = tolower(str[i]);
		lowerCaseString = lowerCaseString + ch;
	}
	return lowerCaseString;
}

