#pragma once
#ifndef __List_H
#define __List_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/statline.h>
#include "IngredientCategories.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "JSON.h"
#include "Alphabetize.h"
#include "Food_Planner_Data.h"

class ListDialog : public wxDialog
{
public:
	ListDialog(const wxString& title, const wxPoint& pos, const wxSize& size);
	void CloseDialog(wxCloseEvent& event);
	void update(wxShowEvent& event);
};

class ListScrollPanel : public wxScrolledWindow
{
private:
	void cleanUp();
	void deleteCategoryFromChoiceBox(wxString category);
	void deleteOrderFromChoiceBox(wxString order);
	void DisplayAndSaveCategoryInOrder(std::string category, std::string order);
	void formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth);
	int getLongestTextSize(wxChoice* choice);
	void insertOrderToChoiceBox(wxString order);

	bool findCategoryInDisplay(std::string category);
	bool findInChoice(std::string name, wxChoice* choice);

public:
	ListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string test_path);
	int frameWidth;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	const int skipLine = 20;
	wxStaticText* StoreNameLabel;
	wxStaticText* CategoryEntryLabel;
	wxStaticText* OrderEntryLabel;
	wxStaticText* SelectStoreNameLabel;
	wxStaticText* orderInfoHeader;
	wxStaticText* orderHeader;
	wxTextCtrl* StoreNameEdit;
	wxChoice* StoreNameEntry;
	wxChoice* CategoryEntry;
	wxChoice* OrderEntry;
	wxButton* EnterCategoryInOrder;
	wxButton* Delete;
	wxButton* Save;
	wxButton* Exit;
	wxButton* SelectList;
	wxButton* EditCategory;
	wxBoxSizer* sizers[9];
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* categorySizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* ListSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticLine* nameLine;
	wxStaticLine* categoryLine;
	std::vector<wxString> CategoryEntryChoices;
	std::vector<wxString> OrderEntryChoices;
	struct categoryOrderGroup {
		wxButton* deleteCategory;
		wxStaticText* categoryLabel;
		wxStaticText* orderLabel;
		wxBoxSizer* newCategorySizer;
		std::string order;
		std::string ingredientCategory;
	};
	std::vector<categoryOrderGroup> categoryOrderGroups;
	List item;
	void DeleteCategory(wxCommandEvent& event);
	void DeletePressed(wxCommandEvent& event, std::string test_path);
	void EditCategoryPressed(wxCommandEvent& event);
	void EnterCategoryInOrderPressed(wxCommandEvent& event);
	void ExitPressed(wxCommandEvent& event);
	void SavePressed(wxCommandEvent& event, std::string test_path);
	void SelectListPressed(wxCommandEvent& event);
	void updateCategories();
	void updateListNames();
	void updateOrder();
};
enum
{
	//for ExistingListFrame
	STATIC_TEXT_StoreNameLabel2,
	STATIC_TEXT_SelectOrderLabel2,
	STATIC_TEXT_CategoryEntryLabel2,
	STATIC_TEXT_OrderEntryLabel2,
	CHOICE_CategoryEntry2,
	CHOICE_OrderEntry2,
	CHOICE_StoreNameEntry2,
	BUTTON_EnterCategoryInOrder2,
	BUTTON_CancelOrganizeList2,
	BUTTON_OkOrganizeList2,
	BUTTON_SelectList
};

extern ListDialog* ListWin;
extern ListScrollPanel* ListPanel;


#endif