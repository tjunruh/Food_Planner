#pragma once
#ifndef __NewMeal_H
#define __NewMeal_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "JSON.h"
class NewMealFrame : public wxFrame
{
public:
	NewMealFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseFrame(wxCloseEvent& event, wxFrame* MainWin);

	//DECLARE_EVENT_TABLE()

};

class NewMealScrollPanel : public wxScrolledWindow
{
private:
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
	void cleanUp();
	void DisplayAndSaveCategory(std::string category);
	void DisplayAndSaveIngredient(Ingredient item);
public:
	NewMealScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, SavedInfo save, JSON infoHandler);
	int frameWidth;
	wxStaticText* MealNameLabel;
	wxStaticText* IngredientsNameLabel;
	wxStaticText* IngredientsUnitLabel;
	wxStaticText* IngredientsAmountLabel;
	wxStaticText* IngredientsCategoryLabel;
	wxStaticText* IngredientInfoHeader;
	wxStaticText* IngredientHeader;
	wxStaticText* CategoryInfoHeader;
	wxStaticText* CategoryHeader;
	wxTextCtrl* MealNameEntry;
	wxTextCtrl* IngredientsNameEntry;
	wxTextCtrl* IngredientsAmountEntry;
	wxChoice* SelectMealCategoriesEntry;
	wxChoice* IngredientsUnitEntry;
	wxChoice* IngredientsCategoryEntry;
	wxButton* EnterIngredient;
	wxButton* EnterCategory;
	wxButton* Cancel;
	wxButton* Ok;
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ingredientSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* categorySizer = new wxBoxSizer(wxVERTICAL);
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
	void EnterIngredientPressed(wxCommandEvent& event);
	void CancelPressed(wxCommandEvent& event);
	void EnterCategoryPressed(wxCommandEvent& event);
	void OkPressed(wxCommandEvent& event, SavedInfo save, JSON infoHandler, std::string saved_info_path);
	void DeleteCategory(wxCommandEvent& event);
	void DeleteIngredient(wxCommandEvent& event);

};
enum {
	//for NewMealFrame
	STATIC_TEXT_MealNameLabel,
	STATIC_TEXT_IngredientsNameLabel,
	STATIC_TEXT_IngredientsAmountLabel,
	STATIC_TEXT_IngredientsUnitLabel,
	STATIC_TEXT_IngredientsCategoryLabel,
	STATIC_TEXT_SelectMealCategoriesLabel,
	TEXT_MealNameEntry,
	TEXT_IngredientsNameEntry,
	TEXT_IngredientsAmountEntry,
	CHOICE_IngredientsUnitEntry,
	CHOICE_IngredientsCategoryEntry,
	CHOICE_SelectMealCategoriesEntry,
	BUTTON_EnterIngredient,
	BUTTON_EnterCategory,
	BUTTON_Cancel,
	BUTTON_Ok
};

#endif