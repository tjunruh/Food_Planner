#pragma once
#ifndef __MealCategories_H
#define __MealCategories_H
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

class MealCategoriesDialog : public wxDialog
{

public:
	MealCategoriesDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};
class MealCategoriesScrollPanel : public wxScrolledWindow
{
private:
	
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
	
public:
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	MealCategoriesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	wxStaticText* Directions;
	wxStaticText* categoriesHeader;
	wxTextCtrl* MealCategoryEntry;
	wxBoxSizer* sizers[3];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* categorySizer = new wxBoxSizer(wxVERTICAL);
	struct displayCategoryInfoGroup {
		wxButton* renameCategory;
		wxStaticText* categoryLabel;
		wxBoxSizer* newCategorySizer;
		wxBoxSizer* spacer;
		std::string category;
	};
	std::vector<displayCategoryInfoGroup> displayCategoryInfoGroups;
	void cleanUp();
	void RenameCategory(wxCommandEvent& event);
	void DisplayCategory(std::string category);
	void DisplayCategories(std::vector<wxString> categories);
	void EnterCategory(wxCommandEvent& event, std::string saved_info_path);
	void SaveCategories(std::string save_file_path);
};

extern MealCategoriesDialog* MealCategoriesWin;
extern MealCategoriesScrollPanel* MealCategoriesPanel;
#endif