#pragma once
#ifndef __JSON_H
#define __JSON_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <string>
#include <vector>
#include <fstream>
#include "Calender.h"
#include "Food_Planner_Data.h"

class JSON
{
private:
	int index;
	std::string text;
	std::string data;

public:
	void handleComma();
	void handleColon();
	void handleEndSquareBracket();
	void handleEndSquiglyBracket();
	void handleSemiColon();
	bool endLine();
	bool endFile();
	std::string ParseStringLabel();
	std::string ParseStringValue();
	Ingredient* ParseIngredientValue();
	std::vector<std::string> ParseStringArray();
	std::vector<Ingredient> ParseIngredientArray();
	//Categories ParseCategories();
	Meal* ParseMealValue();
	List* ParseListValue();
	ChosenMeal* ParseChosenMealValue();
	std::vector<std::string> ParseUnits();
	std::vector<std::string> ParseMealCategories();
	std::vector<std::string> ParseIngredientCategories();
	std::vector<std::string> ParsePantryCategories();
	std::vector<std::string> ParseIngredientNames();
	SavedInfo Parse(std::string message);
	std::string read_file(std::string file_path);
	bool write_file(std::string file_path, std::string message);
	
	void Stringify_Comma();
	void Stringify_Colon();
	void Stringify_BeginSquareBracket();
	void Stringify_EndSquareBracket();
	void Stringify_BeginSquiglyBracket();
	void Stringify_EndSquiglyBracket();
	void Stringify_EndLine();
	void Stringify_EndFile();
	
	void Stringify_Label(std::string label);
	void Stringify_StringValue(std::string item);
	void Stringify_IntValue(int item);
	void Stringify_StringArray(std::vector<std::string> items);
	void Stringify_IngredientValue(Ingredient item);
	void Stringify_IngredientArray(std::vector<Ingredient> items);
	void Stringify_ChosenMeal(ChosenMeal item);
	void Stringify_Units(std::vector<std::string> item);
	void Stringify_MealCategories(std::vector<std::string> item);
	void Stringify_IngredientCategories(std::vector<std::string> item);
	void Stringify_PantryCategories(std::vector<std::string> item);
	void Stringify_IngredientNames(std::vector<std::string> item);
	void Stringify_Meal(Meal item);
	void Stringify_List(List item);
	std::string Stringify(SavedInfo object);
	
};

extern JSON fileReaderWriter;

#endif