#pragma once
#ifndef __IngredientNames_H
#define __IngredientNames_H
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

class IngredientNamesDialog : public wxDialog
{

public:
	IngredientNamesDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};

class IngredientNamesScrollPanel : wxScrolledWindow
{

private:
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
public:
	IngredientNamesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	wxStaticText* Directions;
	wxStaticText* ingredientHeader;
	wxTextCtrl* IngredientNameEntry;
	wxBoxSizer* sizers[3];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ingredientSizer = new wxBoxSizer(wxVERTICAL);
	struct displayInfoGroup {
		wxButton* renameName;
		wxStaticText* nameLabel;
		wxBoxSizer* newNameSizer;
		wxBoxSizer* spacer;
		std::string name;
	};
	std::vector<displayInfoGroup> displayInfoGroups;
	void cleanUp();
	void RenameName(wxCommandEvent& event);
	void DisplayIngredientName(std::string name);
	void DisplayIngredientNames(std::vector<wxString> names);
	void EnterName(wxCommandEvent& event, std::string saved_info_path);
	void SaveNames(std::string saved_info_path);
};

extern IngredientNamesDialog* IngredientNamesWin;
extern IngredientNamesScrollPanel* IngredientNamesPanel;

#endif