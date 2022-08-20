#include "NewList.h"

NewListScrollPanel::NewListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, SavedInfo save, JSON infoHandler) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	const int horizontalMargin = 50;
	const int verticalMargin = 2;
	const int skipLine = 20;
	for (int i = 0; i < 7; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}

	StoreNameLabel = new wxStaticText(this, STATIC_TEXT_StoreNameLabel, wxT("Store Name: "));
	StoreNameEntry = new wxTextCtrl(this, TEXT_StoreNameEntry, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[0]->Add(StoreNameLabel);
	sizers[0]->Add(StoreNameEntry);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	orderInfoHeader = new wxStaticText(this, STATIC_TEXT_SelectOrderLabel, wxT("Select Order:"));
	sizers[1]->Add(orderInfoHeader);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	CategoryEntryChoices = infoHandler.GetAvailableIngredientCategories(save);
	CategoryEntryLabel = new wxStaticText(this, STATIC_TEXT_CategoryEntryLabel, wxT("Ingredient Categories: "));
	CategoryEntry = new wxChoice(this, CHOICE_CategoryEntry, wxDefaultPosition, wxDefaultSize, CategoryEntryChoices.size(), CategoryEntryChoices.data());
	sizers[2]->Add(CategoryEntryLabel);
	sizers[2]->Add(CategoryEntry);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, verticalMargin);

	//OrderEntryChoices.push_back("Unused");
	for (int i = 1; i < CategoryEntryChoices.size() + 1; i++) {
		OrderEntryChoices.push_back(std::to_string(i));
	}
	OrderEntryLabel = new wxStaticText(this, STATIC_TEXT_OrderEntryLabel, wxT("Select position: "));
	OrderEntry = new wxChoice(this, CHOICE_OrderEntry, wxDefaultPosition, wxDefaultSize, OrderEntryChoices.size(), OrderEntryChoices.data());
	sizers[3]->Add(OrderEntryLabel);
	sizers[3]->Add(OrderEntry);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, verticalMargin);

	EnterCategoryInOrder = new wxButton(this, BUTTON_EnterCategoryInOrder, wxT("Enter category order"));
	sizers[4]->Add(EnterCategoryInOrder);
	formatSizer(sizers[4], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[4]);
	mainSizer->Add(0, skipLine);

	orderHeader = new wxStaticText(this, wxID_ANY, wxT("Order:"));
	sizers[5]->Add(orderHeader);
	formatSizer(sizers[5], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[5]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(categorySizer);
	mainSizer->Add(0, skipLine);

	CancelOrganizeList = new wxButton(this, BUTTON_CancelOrganizeList, wxT("Cancel"));
	OkOrganizeList = new wxButton(this, BUTTON_OkOrganizeList, wxT("Ok"));
	sizers[6]->Add((frameWidth - CancelOrganizeList->GetSize().x - OkOrganizeList->GetSize().x - 20) / 2, 0);
	sizers[6]->Add(CancelOrganizeList);
	sizers[6]->Add(20, 0);
	sizers[6]->Add(OkOrganizeList);
	mainSizer->Add(sizers[6]);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
NewListFrame::NewListFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame*)NULL, -1, title, pos, size)
{
	
}

// NewListFrame functions
void NewListScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
	int items = sizer->GetItemCount();
	int usedSpace = 0;
	int openSpace = 0;
	for (int i = 0; i < items; i++) {
		usedSpace = usedSpace + sizer->GetItem(i)->GetSize().x;
	}
	int spaces = items - 1;
	openSpace = frameWidth - usedSpace - (2 * margin);
	sizer->Insert(0, margin, 0);
	if (items == 1) {
		sizer->Insert(1, openSpace / 2, 0);
	}
	else {
		for (int i = 2; i < (items + spaces); i = i + 2) {
			sizer->Insert(i, (openSpace / spaces), 0);
		}
	}
}
void NewListScrollPanel::cleanUp() {
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		insertOrderToChoiceBox(categoryOrderGroups[i].order);
		CategoryEntry->Append(categoryOrderGroups[i].ingredientCategory);
		categoryOrderGroups[i].newCategorySizer->Clear(TRUE);
	}
	mainSizer->Layout();
	categoryOrderGroups.clear();
	item.StoreName = "";
	item.Order.clear();
	item.IngredientCategories.clear();
	StoreNameEntry->SetValue("");
}
void NewListScrollPanel::insertOrderToChoiceBox(wxString order) {
	int insertionIndex = 0;
	for (int i = 0; i < OrderEntry->GetCount(); i++) {
		if (wxAtoi(OrderEntry->GetString(i)) >= wxAtoi(order)) {
			insertionIndex = i;
			break;
		}
		if (i == OrderEntry->GetCount() - 1) {
			insertionIndex = i + 1;
		}
	}
	OrderEntry->Insert(order, insertionIndex);
}
void NewListScrollPanel::EnterCategoryInOrderPressed(wxCommandEvent& WXUNUSED(event)) {
	// Get position of selections within the choice boxes
	int categoryIndex = CategoryEntry->GetSelection();
	int orderIndex = OrderEntry->GetSelection();

	// Check to make sure choices have been made
	if ((categoryIndex != wxNOT_FOUND) && (orderIndex != wxNOT_FOUND)) {

		// Get the choices based on their positions
		std::string category = std::string((CategoryEntry->GetString(categoryIndex)).mb_str());
		std::string order = std::string((OrderEntry->GetString(orderIndex)).mb_str());

		// Delete the order from the choice box
		OrderEntry->Delete(orderIndex);

		DisplayCategoryInOrder(category, order);

		// Delete the category from the choice box
		CategoryEntry->Delete(categoryIndex);
	}
	else {
		wxMessageBox("Enter a category and order.");
	}
}
void NewListScrollPanel::CancelPressed(wxCommandEvent& WXUNUSED(event)) {
	cleanUp();
}
void NewListScrollPanel::OkPressed(wxCommandEvent& WXUNUSED(event), SavedInfo save, JSON infoHandler, std::string test_path) {
	if (StoreNameEntry->GetValue() != "") {
		item.StoreName = StoreNameEntry->GetValue();
		for (int i = 0; i < categoryOrderGroups.size(); i++) {
			item.IngredientCategories.push_back(categoryOrderGroups[i].ingredientCategory);
			item.Order.push_back(categoryOrderGroups[i].order);
		}
		save = infoHandler.setList(save, item);
		infoHandler.write_file(test_path, infoHandler.Stringify(save));
		cleanUp();
	}
	else {
		wxMessageBox("Enter the name of the store.");
	}
}
void NewListFrame::CloseFrame(wxCloseEvent& WXUNUSED(event), wxFrame* MainWin) {
	MainWin->SetPosition(GetPosition());
	MainWin->SetSize(GetSize());
	Show(FALSE);
	MainWin->Show(TRUE);
}
void NewListScrollPanel::DisplayCategoryInOrder(std::string category, std::string order) {
	int index = 0;
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		std::string number = "";
		number = categoryOrderGroups[i].order;
		if (stoi(number) < stoi(order)) {
			index = index + 1;
		}
	}

	categoryOrderGroup group;
	group.categoryLabel = new wxStaticText(this, wxID_ANY, order + " " + category);
	group.deleteCategory = new wxButton(this, wxID_ANY, wxT("x"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.order = order;
	group.ingredientCategory = category;

	group.newCategorySizer->Add(group.categoryLabel);
	group.newCategorySizer->Add(group.deleteCategory);
	
	formatSizer(group.newCategorySizer, 75, frameWidth);
	categorySizer->Insert(index, group.newCategorySizer);

	mainSizer->Layout();

	group.deleteCategory->Bind(wxEVT_BUTTON, &NewListScrollPanel::DeleteCategory, this);
	categoryOrderGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void NewListScrollPanel::DeleteCategory(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	std::string category = "";
	wxString order = "";

	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		if (categoryOrderGroups[i].deleteCategory->GetId() == button) {
			index = i;
			break;
		}
	}

	// Get the category and order from the saved category and order positions and then delete them.
	category = categoryOrderGroups[index].ingredientCategory;
	order = categoryOrderGroups[index].order;

	// Add the deleted category back to the choice box
	CategoryEntry->Append(category);

	insertOrderToChoiceBox(order);

	// Remove the sizer and delete it.
	categoryOrderGroups[index].newCategorySizer->Clear(TRUE);
	
	// Refresh the display
	mainSizer->Layout();

	// Delete the button, label, and sizer from their cooresponding vector
	categoryOrderGroups.erase(categoryOrderGroups.begin() + index);
}