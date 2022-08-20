#pragma once
#ifndef __RenameData_H
#define __RenameData_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/statline.h>
#include "Food_Planner_Data.h"
#include "Alphabetize.h"
#include "JSON.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class renameDataDialog : public wxDialog {
public:
	renameDataDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void closeDialog(wxCloseEvent& event);
};

class renameDataScrollPanel : public wxScrolledWindow {
public:
	renameDataScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	int frameWidth;
	const int horizontalMargin = 50;
	const int skipLine = 20;
	const int verticalMargin = 2;
	int mode;
	wxStaticText* DirectionsHeader;
	wxStaticText* DependanciesHeader;
	wxStaticText* oldNameLabel;
	wxButton* Rename;
	wxChoice* oldNameEntry;
	wxTextCtrl* newNameEntry;
	wxRadioBox* oldOrNewName;
	wxStaticLine* topLine;
	wxStaticLine* bottomLine;
	wxBoxSizer* sizers[6];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* displaySizer = new wxBoxSizer(wxVERTICAL);
	struct displayGroup {
		wxStaticText* label;
		wxBoxSizer* newLabelSizer;
		wxBoxSizer* spacer;
	};
	std::vector<displayGroup> displayGroups;
	void cleanUp();
	void displaySingleData(wxString text);
	void displayMultipleData(std::vector<std::string> text);
	void formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth);
	int getLongestTextSize(wxChoice* choice);
	void RenamePressed(wxCommandEvent& event, std::string saved_info_path);
	void oldOrNewNamePressed(wxCommandEvent& event);
	void updateOldNames(std::vector<wxString> labels);
	void setMode(int selectedMode);
	void setOldName(std::string name);
	void setExistingNames();
	void setUp(int selectMode, std::string oldName);
	void showNewNames();
	void showOldNames();
	enum {
		ingredientStoreCategories = 0,
		ingredientNames = 1,
		units = 2,
		mealCategories = 3,
		ingredientPantryCategories = 4
	};
};
extern renameDataDialog* renameDataWin;
extern renameDataScrollPanel* renameDataPanel;
#endif