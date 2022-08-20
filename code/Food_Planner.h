#pragma once
#ifndef __Food_Planner_H
#define __Food_Planner_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "JSON.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include "Meal.h"
#include "List.h"
#include "Calender.h"
#include "MealPicker.h"
#include "previewList.h"
#include "BuildList.h"
#include <string>
#include "RenameData.h"

class MainApp : public wxApp
{

public:
	virtual bool OnInit();
};

class MainFrame : public wxFrame
{
private:
	
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	wxMenuBar* MainMenu;
	wxMenu* FileMenu;
	wxMenu* EditMenu;
	void CheckForClose(wxShowEvent& event);
	void CloseFrame(wxCloseEvent& event);
	void OnMeal(wxCommandEvent& event);
	void OnList(wxCommandEvent& event);
};

class MainScrollPanel : public wxScrolledWindow
{
private:
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
	int getLongestTextSize(wxChoice* choice);
	void updateMealsOrCategories();
	void updateDisplayedChosenMeals();
	void updateMealOfTheDayLabel();
	
	
public:
	MainScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size);
	int frameWidth;
	const int verticalMargin = 2;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	int generateMealClicks = 0;
	monthDayYear beginDate;
	monthDayYear endDate;
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* chosenMealSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizers[12];
	wxStaticText* Date;
	wxStaticText* Range;
	wxStaticText* MealOrCategory;
	wxStaticText* SelectedOrGeneratedMeal;
	wxStaticText* DateRangeHeader;
	wxStaticText* chosenMealsHeader;
	wxStaticText* MealOfTheDay;
	wxButton* LeftDateArrow;
	wxButton* RightDateArrow;
	wxButton* LeftRangeArrow;
	wxButton* RightRangeArrow;
	wxButton* PickMealOrGenerateMeal;
	wxButton* EnterRange;
	wxButton* BuildList;
	wxRadioBox* MealType;
	wxChoice* EnterMealOrEnterCategory;
	wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticLine* topOfMeal;
	wxStaticLine* bottomOfMeal;
	ChosenMeal item;
	struct displayChosenMealInfoGroup {
		wxStaticText* chosenMealLabel;
		std::string chosenMealName;
		wxBoxSizer* newChosenMealSizer;
		wxBoxSizer* spacer;
	};
	std::vector<displayChosenMealInfoGroup> displayChosenMealInfoGroups;
	void buildListPressed(wxCommandEvent& event);
	void displayChosenMeal(ChosenMeal item);
	void LeftDateArrowPressed(wxCommandEvent& event);
	void RightDateArrowPressed(wxCommandEvent& event);
	void LeftRangeArrowPressed(wxCommandEvent& event);
	void RightRangeArrowPressed(wxCommandEvent& event);
	void MealTypeSpecificOrCategory(wxCommandEvent& event);
	void EnterRangePressed(wxCommandEvent& event);
	void PickMealOrGenerateMealPressed(wxCommandEvent& event);
	void CategoryPicked(wxCommandEvent& event);
	void updateMealOrCategory();
	void updateMealOfTheDay();
	void updatePickMealOrGenerateMeal();
};


enum {
	//for MainFrame
	STATIC_TEXT_Date = wxID_HIGHEST + 1,
	STATIC_TEXT_MealOrCategory,
	STATIC_TEXT_SelectedOrGeneratedMeal,
	BUTTON_LeftArrow,
	BUTTON_RightArrow,
	BUTTON_Save,
	RADIO_BOX_MealType,
	CHOICE_EnterMealOrEnterCategory,
	MENU_PrintGroceryList,
	MENU_PrintMealPlan,
	MENU_SaveGroceryListAsPDF,
	MENU_SaveMealPlanAsPDF,
	MENU_Meal,
	MENU_MealCategory,
	MENU_IngredientCategory,
	MENU_OrganizeList,
	MENU_List,
	MENU_Units
};

extern MainFrame* MainWin;
extern MainScrollPanel* MainPanel;
#endif