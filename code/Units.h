#pragma once
#ifndef __Units_H
#define __Units_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "JSON.h"
#include "Alphabetize.h"
#include "InputValidator.h"
#include "RenameData.h"

class UnitsDialog : public wxDialog
{
public:
	UnitsDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
};

class UnitsScrollPanel : public wxScrolledWindow
{
private:
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
public:
	UnitsScrollPanel(wxWindow* parent, wxWindowID id, const wxSize&, std::string saved_info_path);
	int frameWidth;
	const int skipLine = 20;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	wxStaticText* Directions;
	wxStaticText* UnitsHeader;
	wxTextCtrl* UnitEntry;
	wxBoxSizer* sizers[3];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* unitSizer = new wxBoxSizer(wxVERTICAL);
	struct displayCategoryInfoGroup {
		wxButton* renameUnit;
		wxStaticText* unitLabel;
		wxBoxSizer* newUnitSizer;
		wxBoxSizer* spacer;
		std::string unit;
	};
	std::vector<displayCategoryInfoGroup> displayInfoGroups;
	void cleanUp();
	void EnterUnit(wxCommandEvent& event, std::string saved_info_path);
	void RenameUnit(wxCommandEvent& event);
	void DisplayUnit(std::string unit);
	void DisplayUnits(std::vector<wxString> units);
	void SaveUnit(std::string saved_info_path);
};

extern UnitsDialog* UnitsWin;
extern UnitsScrollPanel* UnitsPanel;

#endif