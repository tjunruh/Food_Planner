#include "JSON.h"

JSON fileReaderWriter;

void JSON::handleComma() {
	if (text[index] == ',') {
		index = index + 1;
		if (text[index] == ' ') {
			index = index + 1;
		}
	}
}

void JSON::handleColon() {
	if (text[index] == ':') {
		index = index + 1;
	}
}

void JSON::handleEndSquareBracket() {
	if (text[index] == ']') {
		index = index + 1;
	}
}

void JSON::handleEndSquiglyBracket() {
	if (text[index] == '}') {
		index = index + 1;
	}
}

void JSON::handleSemiColon() {
	if ((text[index] == ';') && (text[index + 1] != '!')) {
		index = index + 2;
	}
	else if (text[index + 1] == '!') {
		index = index + 1;
	}
}

bool JSON::endLine() {
	bool endLine = false;
	if (text[index] == ';') {
		endLine = true;
	}
	return endLine;
}

bool JSON::endFile() {
	bool endFile = false;
	if (text[index] == '!') {
		endFile = true;
	}
	return endFile;
}

std::string JSON::ParseStringLabel() {
	std::string label = "";
	if (text[index] == '{') {
		index = index + 1;
	}
	else if (text[index] == '[') {
		index = index + 1;
	}
	while (text[index] != ':') {
		label = label + text[index];
		index = index + 1;
	}
	return label;
}

std::string JSON::ParseStringValue() {
	std::string item = "";
	if (text[index] == '[') {
		index = index + 1;
	}
	if (text[index] == '{') {
		index = index + 1;
	}
	while ((text[index] != ',') && (text[index] != ']') && (text[index] != '}')) {
		item = item + text[index];
		index = index + 1;
	}
	return item;
}

Ingredient* JSON::ParseIngredientValue() {
	Ingredient* info = new Ingredient;
	std::string label;
	std::string value;
	std::string query;

	while (text[index] != '}') {
		label = ParseStringLabel();
		handleColon();
		value = ParseStringValue();
		handleComma();
		if (label == "Name") {
			info->Name = value;
		}
		else if (label == "storeCategory") {
			info->storeCategory = value;
		}
		else if (label == "pantryCategory") {
			info->pantryCategory = value;
		}
		else if (label == "Unit") {
			info->Unit = value;
		}
		else if (label == "Amount") {
			info->Amount = std::stod(value);
		}
	}
	handleEndSquiglyBracket();
	handleComma();
	return info;
}

std::vector<std::string> JSON::ParseStringArray() {
	std::vector<std::string>StackOfInfo;
	std::string item = "";

	while (text[index] != ']') {
		item = ParseStringValue();
		handleComma();
		StackOfInfo.push_back(item);
	}
	handleEndSquareBracket();
	handleComma();
	return StackOfInfo;
}

std::vector<Ingredient> JSON::ParseIngredientArray() {
	Ingredient* item = new Ingredient;
	std::vector<Ingredient> ListOfInfo;
	while (text[index] != ']') {
		ParseStringLabel();
		handleColon();
		item = ParseIngredientValue();
		handleComma();
		ListOfInfo.push_back(*item);
	}
	handleEndSquareBracket();
	handleComma();
	return ListOfInfo;
}

Meal* JSON::ParseMealValue() {
	Meal* object = new Meal;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "Name") {
			object->Name = ParseStringValue();
			handleComma();
		}
		else if (label == "Categories") {
			object->Categories = ParseStringArray();
			handleComma();
		}
		else if (label == "Ingredients") {
			object->Ingredients = ParseIngredientArray();
			handleComma();
		}
		label = "";
		handleEndSquiglyBracket();
		handleComma();
	}

	return object;
}

List* JSON::ParseListValue() {
	List* object = new List;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "StoreName") {
			object->StoreName = ParseStringValue();
			handleComma();
		}
		else if (label == "Order") {
			object->Order = ParseStringArray();
			handleComma();
		}
		else if (label == "IngredientCategories") {
			object->IngredientCategories = ParseStringArray();
			handleComma();
		}
		label = "";
		handleEndSquiglyBracket();
		handleComma();
	}

	return object;
}

ChosenMeal* JSON::ParseChosenMealValue() {
	ChosenMeal* object = new ChosenMeal;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "MealName") {
			object->mealName = ParseStringValue();
			handleComma();
		}
		else if (label == "Month") {
			object->date.month = stoi(ParseStringValue());
			handleComma();
		}
		else if (label == "Day") {
			object->date.day = stoi(ParseStringValue());
			handleComma();
		}
		else if (label == "Year") {
			object->date.year = stoi(ParseStringValue());
			handleComma();
		}
		label = "";
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

std::vector<std::string> JSON::ParseUnits() {
	std::vector<std::string> object;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "Units") {
			object = ParseStringArray();
			handleComma();
		}
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

std::vector<std::string> JSON::ParseMealCategories() {
	std::vector<std::string> object;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "MealCategories") {
			object = ParseStringArray();
			handleComma();
		}
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

std::vector<std::string> JSON::ParseIngredientCategories() {
	std::vector<std::string> object;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "IngredientCategories") {
			object = ParseStringArray();
			handleComma();
		}
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

std::vector<std::string> JSON::ParsePantryCategories() {
	std::vector<std::string> object;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "PantryCategories") {
			object = ParseStringArray();
			handleComma();
		}
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

std::vector<std::string> JSON::ParseIngredientNames() {
	std::vector<std::string> object;
	std::string label = "";
	while (!endLine()) {
		label = ParseStringLabel();
		handleColon();
		if (label == "IngredientNames") {
			object = ParseStringArray();
			handleComma();
		}
		handleEndSquiglyBracket();
		handleComma();
	}
	return object;
}

SavedInfo JSON::Parse(std::string message) {
	text = message;
	SavedInfo object;
	if (text != "") {
		Meal* mealItem = new Meal;
		List* listItem = new List;
		ChosenMeal* chosenMealItem = new ChosenMeal;
		std::vector<Meal> ListOfMeals;
		std::vector<List> ListOfLists;
		std::vector<ChosenMeal> ListOfChosenMeals;
		std::vector<std::string> mealCategories;
		std::vector<std::string> ingredientCategories;
		std::vector<std::string> Units;
		std::vector<std::string> ingredientNames;
		std::vector<std::string> pantryCategories;
		std::string label = "";
		int index = 0;
		while (!endFile()) {
			label = ParseStringLabel();
			handleColon();
			if (label == "Meal") {
				mealItem = ParseMealValue();
				handleSemiColon();
				ListOfMeals.push_back(*mealItem);
			}
			else if (label == "List") {
				listItem = ParseListValue();
				handleSemiColon();
				ListOfLists.push_back(*listItem);
			}
			else if (label == "ChosenMeal") {
				chosenMealItem = ParseChosenMealValue();
				handleSemiColon();
				ListOfChosenMeals.push_back(*chosenMealItem);
			}
			else if (label == "MealCategories") {
				mealCategories = ParseMealCategories();
				handleSemiColon();
			}
			else if (label == "IngredientCategories") {
				ingredientCategories = ParseIngredientCategories();
				handleSemiColon();
			}
			else if (label == "Units") {
				Units = ParseUnits();
				handleSemiColon();
			}
			else if (label == "IngredientNames") {
				ingredientNames = ParseIngredientNames();
				handleSemiColon();
			}
			else if (label == "PantryCategories") {
				pantryCategories = ParsePantryCategories();
				handleSemiColon();
			}
		}
		object.meal = ListOfMeals;
		object.list = ListOfLists;
		object.chosenmeal = ListOfChosenMeals;
		object.mealCategories = mealCategories;
		object.storeCategories = ingredientCategories;
		object.pantryCategories = pantryCategories;
		object.units = Units;
		object.ingredientNames = ingredientNames;
	}
	
	index = 0;
	return object;
}

//std::string* JSON::vectorToArray(std::vector<std::string> vectorInfo) {
//	std::string* refArr = vectorInfo.data();
//	int size = vectorInfo.size();
//	return refArr;
//}

std::string JSON::read_file(std::string file_path) {
	std::ifstream file(file_path);
	std::string message;

	if (file.is_open()) {
		char letter[1];
		while (!file.eof()) {
			file.read(letter, 1);
			message = message + letter[0];
		}
		message.erase((message.length() - 1), 1);
		file.close();
	}
	else {
		//cout << "Cannot find file.\n" << endl;
		message = "";
	}
	return message;
}

bool JSON::write_file(std::string file_path, std::string message) {
	bool success = false;
	std::ofstream file(file_path);//std::ofstream::out | std::ofstream::trunc);
	if (file.is_open()) {
		file << message << std::endl;
		success = true;
	}
	else {
		success = false;
	}
	return success;
}

void JSON::Stringify_Comma() {
	data = data + ", ";
}

void JSON::Stringify_Colon() {
	data = data + ":";
}

void JSON::Stringify_BeginSquareBracket() {
	data = data + "[";
}

void JSON::Stringify_EndSquareBracket() {
	data.erase((data.length() - 2), 2);
	data = data + "]";
}

void JSON::Stringify_BeginSquiglyBracket() {
	data = data + "{";
}
void JSON::Stringify_EndSquiglyBracket() {
	data.erase((data.length() - 2), 2);
	data = data + "}";
}

void JSON::Stringify_EndLine() {
	data = data + ";\n";
}

void JSON::Stringify_EndFile() {
	data.erase((data.length() - 1), 1);
	data = data + "!";
}
void JSON::Stringify_Label(std::string label) {
	data = data + label;
	Stringify_Colon();
}

void JSON::Stringify_StringValue(std::string item) {
	data = data + item;
	Stringify_Comma();
}

void JSON::Stringify_IntValue(int item) {
	data = data + std::to_string(item);
	Stringify_Comma();
}

void JSON::Stringify_StringArray(std::vector<std::string> items) {
	int size = items.size();
	Stringify_BeginSquareBracket();
	for (int i = 0; i < size; i++) {
		Stringify_StringValue(items[i]);
	}
	Stringify_EndSquareBracket();
	Stringify_Comma();
}

void JSON::Stringify_IngredientValue(Ingredient item) {
	Stringify_BeginSquiglyBracket();
	Stringify_Label("Name");
	Stringify_StringValue(item.Name);
	Stringify_Label("storeCategory");
	Stringify_StringValue(item.storeCategory);
	Stringify_Label("pantryCategory");
	Stringify_StringValue(item.pantryCategory);
	Stringify_Label("Unit");
	Stringify_StringValue(item.Unit);
	Stringify_Label("Amount");
	Stringify_StringValue(std::to_string(item.Amount));
	Stringify_EndSquiglyBracket();
	Stringify_Comma();
}

void JSON::Stringify_IngredientArray(std::vector<Ingredient> items) {
	Ingredient* refArr = items.data();
	int size = items.size();
	Stringify_BeginSquareBracket();
	for (int i = 0; i < size; i++) {
		Stringify_Label("Ingredient");
		Stringify_IngredientValue(items[i]);
	}
	Stringify_EndSquareBracket();
	Stringify_Comma();
}

void JSON::Stringify_Meal(Meal item) {
	Stringify_Label("Meal");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("Name");
	Stringify_StringValue(item.Name);
	Stringify_Label("Categories");
	Stringify_StringArray(item.Categories);
	Stringify_Label("Ingredients");
	Stringify_IngredientArray(item.Ingredients);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_List(List item) {
	Stringify_Label("List");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("StoreName");
	Stringify_StringValue(item.StoreName);
	Stringify_Label("Order");
	Stringify_StringArray(item.Order);
	Stringify_Label("IngredientCategories");
	Stringify_StringArray(item.IngredientCategories);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_ChosenMeal(ChosenMeal item) {
	Stringify_Label("ChosenMeal");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("MealName");
	Stringify_StringValue(item.mealName);
	Stringify_Label("Month");
	Stringify_IntValue(item.date.month);
	Stringify_Label("Day");
	Stringify_IntValue(item.date.day);
	Stringify_Label("Year");
	Stringify_IntValue(item.date.year);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_Units(std::vector<std::string> item) {
	Stringify_Label("Units");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("Units");
	Stringify_StringArray(item);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_MealCategories(std::vector<std::string> item) {
	Stringify_Label("MealCategories");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("MealCategories");
	Stringify_StringArray(item);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_IngredientCategories(std::vector<std::string> item) {
	Stringify_Label("IngredientCategories");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("IngredientCategories");
	Stringify_StringArray(item);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_PantryCategories(std::vector<std::string> item) {
	Stringify_Label("PantryCategories");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("PantryCategories");
	Stringify_StringArray(item);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

void JSON::Stringify_IngredientNames(std::vector<std::string> item) {
	Stringify_Label("IngredientNames");
	Stringify_BeginSquiglyBracket();
	Stringify_Label("IngredientNames");
	Stringify_StringArray(item);
	Stringify_EndSquiglyBracket();
	Stringify_EndLine();
}

std::string JSON::Stringify(SavedInfo object) {
	data = "";
	for (int i = 0; i < object.meal.size(); i++) {
		Stringify_Meal(object.meal[i]);
	}
	for (int i = 0; i < object.list.size(); i++) {
		Stringify_List(object.list[i]);
	}
	for (int i = 0; i < object.chosenmeal.size(); i++) {
		Stringify_ChosenMeal(object.chosenmeal[i]);
	}
	if (object.storeCategories.size() != 0) {
		Stringify_IngredientCategories(object.storeCategories);
	}
	if (object.mealCategories.size() != 0) {
		Stringify_MealCategories(object.mealCategories);
	}
	if (object.units.size() != 0) {
		Stringify_Units(object.units);
	}
	if (object.ingredientNames.size() != 0) {
		Stringify_IngredientNames(object.ingredientNames);
	}
	if (object.pantryCategories.size() != 0) {
		Stringify_PantryCategories(object.pantryCategories);
	}
	Stringify_EndFile();

	return data;
}



