#pragma once

#ifndef __NewList_H
#define __NewList_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "JSON.h"
class NewListFrame : public wxFrame
{

public:
	NewListFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseFrame(wxCloseEvent& event, wxFrame* MainWin);
};

class NewListScrollPanel : public wxScrolledWindow
{
private:
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
	void cleanUp();
	void DisplayCategoryInOrder(std::string category, std::string order);
	void insertOrderToChoiceBox(wxString order);
public:
	NewListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, SavedInfo save, JSON infoHandler);
	int frameWidth;
	wxStaticText* StoreNameLabel;
	wxStaticText* orderInfoHeader;
	wxStaticText* orderHeader;
	wxStaticText* CategoryEntryLabel;
	wxStaticText* OrderEntryLabel;
	wxTextCtrl* StoreNameEntry;
	wxChoice* CategoryEntry;
	wxChoice* OrderEntry;
	wxButton* EnterCategoryInOrder;
	wxButton* CancelOrganizeList;
	wxButton* OkOrganizeList;
	wxBoxSizer* sizers[7];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* categorySizer = new wxBoxSizer(wxVERTICAL);
	std::vector<wxString> CategoryEntryChoices;
	std::vector<wxString> OrderEntryChoices;
	struct categoryOrderGroup {
		wxButton* deleteCategory;
		wxStaticText* categoryLabel;
		wxBoxSizer* newCategorySizer;
		std::string order;
		std::string ingredientCategory;
	};
	std::vector<categoryOrderGroup> categoryOrderGroups;
	List item;
	void EnterCategoryInOrderPressed(wxCommandEvent& event);
	void CancelPressed(wxCommandEvent& event);
	void OkPressed(wxCommandEvent& event, SavedInfo save, JSON infoHandler, std::string test_path);
	void DeleteCategory(wxCommandEvent& event);
};

enum {
	//for OrganizeListFrame
	STATIC_TEXT_StoreNameLabel,
	STATIC_TEXT_SelectOrderLabel,
	STATIC_TEXT_CategoryEntryLabel,
	STATIC_TEXT_OrderEntryLabel,
	TEXT_StoreNameEntry,
	CHOICE_CategoryEntry,
	CHOICE_OrderEntry,
	BUTTON_EnterCategoryInOrder,
	BUTTON_CancelOrganizeList,
	BUTTON_OkOrganizeList
};

#endif