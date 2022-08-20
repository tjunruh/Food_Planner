#pragma once
#ifndef __IngredientCategories_H
#define __IngredientCategories_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "JSON.h"
#include "Food_Planner_Data.h"
#include "Alphabetize.h"
#include "InputValidator.h"
#include "RenameData.h"

class IngredientCategoriesDialog : public wxDialog
{

public:
	IngredientCategoriesDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};

class IngredientCategoriesScrollPanel : wxScrolledWindow
{

private:
	
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
public:
	IngredientCategoriesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	wxStaticText* ingredientHeader;
	wxStaticText* Directions;
	wxTextCtrl* IngredientCategoryEntry;
	wxBoxSizer* sizers[3];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ingredientSizer = new wxBoxSizer(wxVERTICAL);
	struct displayInfoGroup {
		wxButton* deleteCategory;
		wxStaticText* categoryLabel;
		wxBoxSizer* newCategorySizer;
		wxBoxSizer* spacer;
		std::string category;
	};
	std::vector<displayInfoGroup> displayInfoGroups;
	void cleanUp();
	void RenameCategory(wxCommandEvent& event);
	void DisplayCategory(std::string category);
	void DisplayCategories(std::vector<wxString> categories);
	void EnterIngredientCategory(wxCommandEvent& event, std::string saved_info_path);
	void SaveCategories(std::string saved_info_path);
};

extern IngredientCategoriesDialog* IngredientCategoriesWin;
extern IngredientCategoriesScrollPanel* IngredientCategoriesPanel;

#endif