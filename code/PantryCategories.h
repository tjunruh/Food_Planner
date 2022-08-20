#pragma once
#ifndef __PantryCategories_H
#define __PantryCategories_H
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

class PantryCategoriesDialog : public wxDialog
{

public:
	PantryCategoriesDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};
class PantryCategoriesScrollPanel : public wxScrolledWindow
{
private:

	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);

public:
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	PantryCategoriesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	wxStaticText* Directions;
	wxStaticText* categoriesHeader;
	wxTextCtrl* PantryCategoryEntry;
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

extern PantryCategoriesDialog* PantryCategoriesWin;
extern PantryCategoriesScrollPanel* PantryCategoriesPanel;
#endif