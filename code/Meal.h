#pragma once
#ifndef __Meal_H
#define __Meal_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/statline.h>

#include "IngredientCategories.h"
#include "IngredientNames.h"
#include "PantryCategories.h"
#include "Units.h"
#include "MealCategories.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "JSON.h"
#include "Food_Planner_Data.h"
#include "Alphabetize.h"
#include "InputValidator.h"

class MealDialog : public wxDialog
{
private:

public:
	MealDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
	void update(wxShowEvent& event);
};

class MealScrollPanel : public wxScrolledWindow
{
private:
	bool findMealCategoryInDisplay(std::string name);
	bool findInChoice(std::string name, wxChoice* choice);
	bool findIngredientInDisplay(std::string name);

	void cleanUp();
	bool checkIfNumber(std::string str);
	void DeleteCategoryFromChoiceBox(std::string category);
	void DisplayAndSaveCategory(std::string category);
	void DisplayAndSaveIngredient(Ingredient item);
	void formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth);
	int getLongestTextSize(wxChoice* choice);
	std::string round(double num, int decimalPlaces);
	
public:
	MealScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, wxScrolledWindow* MainPanel, std::string test_path);
	float frameWidth;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	const int skipLine = 20;
	//wxStaticText* MealCategoryLabel;
	//wxStaticText* MealNameLabel;
	wxStaticText* MealNameHeader;
	wxStaticText* IngredientsNameLabel;
	wxStaticText* IngredientsUnitLabel;
	wxStaticText* IngredientsAmountLabel;
	wxStaticText* IngredientsStoreCategoryLabel;
	wxStaticText* IngredientsPantryCategoryLabel;
	wxStaticText* IngredientInfoHeader;
	wxStaticText* IngredientHeader;
	wxStaticText* CategoryInfoHeader;
	wxStaticText* CategoryHeader;
	wxTextCtrl* MealNameEntry;
	wxTextCtrl* IngredientsAmountEntry;
	wxChoice* IngredientsUnitEntry;
	wxChoice* IngredientsStoreCategoryEntry;
	wxChoice* IngredientsPantryCategoryEntry;
	wxChoice* IngredientsNameEntry;
	wxChoice* SelectMeal;
	wxChoice* SelectMealCategoriesEntry;
	wxButton* EnterMeal;
	wxButton* EnterIngredient;
	wxButton* EnterCategory;
	wxButton* EditIngredientStoreCategory;
	wxButton* EditIngredientPantryCategory;
	wxButton* EditIngredientName;
	wxButton* EditMealCategory;
	wxButton* EditUnit;
	wxButton* Delete;
	wxButton* Clear;
	wxButton* Save;
	wxButton* Exit;
	wxBoxSizer* horizontalSizers[14] = {};
	wxBoxSizer* verticalSizers[6] = {};
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ingredientSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* categorySizer = new wxBoxSizer(wxVERTICAL);
	wxStaticLine* centerLine;
	wxStaticLine* nameLine;
	wxStaticLine* mealCategoryLine;
	wxStaticLine* IngredientLine;
	struct displayCategoryInfoGroup {
		wxButton* deleteCategory;
		wxStaticText* categoryLabel;
		wxBoxSizer* newCategorySizer;
		wxBoxSizer* spacer;
		std::string category;
	};
	struct displayIngredientInfoGroup {
		wxButton* deleteIngredient;
		wxStaticText* ingredientLabel;
		wxBoxSizer* newIngredientSizer;
		wxBoxSizer* spacer;
		Ingredient ingredient;
	};

	std::vector<displayCategoryInfoGroup> displayCategoryInfoGroups;
	std::vector<displayIngredientInfoGroup> displayIngredientInfoGroups;
	Meal meal;
	void ClearPressed(wxCommandEvent& event);
	void EditIngredientPantryCategoryPressed(wxCommandEvent& event);
	void EditIngredientStoreCategoryPressed(wxCommandEvent& event);
	void EditMealCategoryPressed(wxCommandEvent& event);
	void EditIngredientNamePressed(wxCommandEvent& event);
	void EditUnitPressed(wxCommandEvent& event);
	void EnterCategoryPressed(wxCommandEvent& event);
	void EnterIngredientPressed(wxCommandEvent& event);
	void EnterMealPressed(wxCommandEvent& event);
	void ExitPressed(wxCommandEvent& event);
	void DeleteCategory(wxCommandEvent& event);
	void DeleteIngredient(wxCommandEvent& event);
	void DeletePressed(wxCommandEvent& event, std::string test_path);
	void SavePressed(wxCommandEvent& event, std::string test_path);
	void updateIngredientStoreCategories();
	void updateIngredientPantryCategories();
	void updateIngredientNames();
	void updateMealCategories();
	void updateMealNames();
	void updateUnits();

	//void update(wxShowEvent& event);
};

extern MealDialog* MealWin;
extern MealScrollPanel* MealPanel;
#endif