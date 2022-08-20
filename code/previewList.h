#pragma once
#ifndef __previewList_H
#define __previewList_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "Food_Planner_Data.h"
#include <wx/statline.h>
#include "BuildList.h"
#include "JSON.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Printer.h"

class previewListDialog : public wxDialog {
public:
	previewListDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void closeDialog(wxCloseEvent& event);
	void update(wxShowEvent& event);
};

class previewListScrollPanel : public wxScrolledWindow {
public:
	previewListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string programPath, monthDayYear beginDate, monthDayYear endDate);
	int frameWidth;
	const int horizontalMargin = 50;
	const int skipLine = 20;
	const int verticalMargin = 2;
	wxStaticText* listHeader;
	wxStaticText* storesHeader;
	wxButton* print;
	wxButton* save;
	wxChoice* stores;
	wxStaticLine* aboveIngredients;
	wxStaticLine* belowIngredients;
	wxBoxSizer* sizers[4];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ingredientSizer = new wxBoxSizer(wxVERTICAL);
	struct displayIngredientGroup {
		wxButton* deleteIngredient;
		wxStaticText* ingredientName;
		wxStaticText* unit;
		wxTextCtrl* amount;
		wxBoxSizer* newIngredientSizer;
		wxBoxSizer* spacer;
		std::string category;
	};
	std::vector<displayIngredientGroup> displayIngredientGroups;
	void cleanUp();
	void formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth);
	int getLongestTextSize(wxChoice* choice);
	void DisplayIngredient(Ingredient item);
	void DisplayPantryCategory(wxString category);
	void DeleteIngredient(wxCommandEvent& event);
	void PrintPressed(wxCommandEvent& event);
	void SavePressed(wxCommandEvent& event, std::string programPath, monthDayYear beginDate, monthDayYear endDate);
	std::string round(double num, int decimalPlaces);
	void updateStores();
	void updateDisplayedIngredients();
	
};

extern previewListScrollPanel* previewListPanel;
extern previewListDialog* previewListWin;

#endif

