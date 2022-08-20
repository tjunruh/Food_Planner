#pragma once
#ifndef __Food_Planner_Data_H
#define __Food_Planner_Data_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <vector>
#include <string>
#include "Calender.h"

class Ingredient
{
public:
	std::string Name;
	std::string storeCategory;
	std::string pantryCategory;
	std::string Unit;
	double Amount;
};

class Meal
{
public:
	std::string Name;
	std::vector<std::string> Categories;
	std::vector<Ingredient> Ingredients;
};

class List
{
public:
	std::string StoreName;
	std::vector<std::string> Order;
	std::vector<std::string> IngredientCategories;
};
class ChosenMeal {

public:
	std::string mealName;
	monthDayYear date;
};


class SavedInfo {
	
public:

	std::vector<Meal> meal;
	std::vector<List> list;
	std::vector<ChosenMeal> chosenmeal;
	std::vector<std::string> mealCategories;
	std::vector<std::string> storeCategories;
	std::vector<std::string> ingredientNames;
	std::vector<std::string> units;
	std::vector<std::string> pantryCategories;

	void setMeal(Meal item);
	void setList(List item);
	//void setMealIngredient(Ingredient item, std::string mealName);
	//SavedInfo setMealCategory(SavedInfo info, std::string item, std::string mealName);
	void setMealName(std::string newName, std::string oldName);
	void setListStoreName(std::string newName, std::string oldName);
	//SavedInfo setListIngredientCategory(SavedInfo info, std::string item, std::string storeName);
	//SavedInfo setListOrder(SavedInfo info, std::string item, std::string storeName, int position);
	void setMealCategories(std::vector<std::string> categories);
	void setStoreCategories(std::vector<std::string> category);
	void setPantryCategories(std::vector<std::string> categories);
	//SavedInfo setOverallMealCategories(SavedInfo info, std::vector<std::string> item);
	//SavedInfo setOverallIngredientCategories(SavedInfo info, std::vector<std::string> item);
	void setUnits(std::vector<std::string> unit);
	void setIngredientNames(std::vector<std::string> names);
	void setChosenMeal(ChosenMeal item);
	std::vector<wxString> getIngredientCategories();
	std::vector<wxString> getMealCategories();
	std::vector<wxString> getPantryCategories();
	std::vector<wxString> getUnits();
	std::vector<wxString> getOrder();
	std::vector<wxString> getMealNames();
	std::vector<wxString> getListStoreNames();
	std::vector<wxString> getIngredientNames();
	std::vector<std::string> getMealCategoriesOfMeal(std::string mealName);
	ChosenMeal getChosenMeal(monthDayYear dateInput);
	ChosenMeal getChosenMeal(std::string name);
	std::vector<ChosenMeal> getChosenMeals();
	Meal getMeal(std::string mealName);
	std::vector<Meal> getMeals();
	std::vector<std::string> getMealNamesOfCategory(std::string category);
	std::vector<std::string> getIngredientNamesOfStoreCategory(std::string category);
	std::vector<std::string> getIngredientNamesOfPantryCategory(std::string category);
	std::vector<std::string> getIngredientNamesOfUnit(std::string unit);
	List getList(std::string storeName);
	bool findUnit(wxString unit);
	bool findMealCategory(wxString category);
	bool findIngredientStoreCategory(wxString category);
	bool findIngredientPantryCategory(wxString category);
	bool findIngredientName(wxString name);
	bool findMeal(wxString mealName);
	bool findList(wxString listName);
	void deleteMeal(std::string mealName);
	void deleteList(std::string storeName);
	void renameMealCategory(std::string oldCategory, std::string newCategory);
	void renameIngredientStoreCategory(std::string oldCategory, std::string newCategory);
	void renameIngredientPantryCategory(std::string oldCategory, std::string newCategory);
	void renameIngredient(std::string oldName, std::string newName);
	void renameUnit(std::string oldUnit, std::string newUnit);
	//void deleteMealIngredient(SavedInfo info, std::string mealName, std::string ingredientName);
	//void deleteMealCategory(SavedInfo info, std::string mealName, std::string category);
	//void deleteListCategoryAndOrder(SavedInfo info, std::string storeName, std::string category);
	//void deleteMealCategory(std::string category);
	//void deleteIngredientCategory(std::string category);
};
extern SavedInfo foodPlannerData;
#endif