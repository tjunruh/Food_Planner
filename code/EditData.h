#pragma once
#ifndef __EditData_H
#define __EditData_H
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

class editDataDialog : public wxDialog
{

public:
	editDataDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};
class editDataScrollPanel : public wxScrolledWindow
{
private:

	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);

public:
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	int mode;
	editDataScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path);
	wxStaticText* Directions;
	wxStaticText* dataHeader;
	wxTextCtrl* dataEntry;
	wxBoxSizer* sizers[3];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* dataSizer = new wxBoxSizer(wxVERTICAL);
	struct displayCategoryInfoGroup {
		wxButton* renameData;
		wxStaticText* dataLabel;
		wxBoxSizer* newDataSizer;
		wxBoxSizer* spacer;
		std::string data;
	};
	std::vector<displayCategoryInfoGroup> displayDataInfoGroups;
	void cleanUp();
	void RenameData(wxCommandEvent& event);
	void DisplayData(std::string category);
	void EnterData(wxCommandEvent& event, std::string saved_info_path);
	void SaveData(std::string save_file_path);
	void setMode(int selectedMode);
	enum {
		ingredientStoreCategories = 0,
		ingredientNames = 1,
		units = 2,
		mealCategories = 3,
		ingredientPantryCategories = 4
	};
};

extern editDataDialog* editDataWin;
extern editDataScrollPanel* editDataPanel;
#endif