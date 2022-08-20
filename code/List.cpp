#include "List.h"

ListDialog* ListWin;
ListScrollPanel* ListPanel;
ListScrollPanel::ListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string test_path) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	wxFont headerFont = wxFont(wxFontInfo(12).Bold().Underlined());
	for (int i = 0; i < 9; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	std::vector<wxString> choices1 = foodPlannerData.getListStoreNames();
	SelectList = new wxButton(this, wxID_ANY, wxT("Select List"));
	StoreNameEntry = new wxChoice(this, CHOICE_StoreNameEntry2, wxDefaultPosition, wxDefaultSize, choices1.size(), choices1.data());
	sizers[0]->Add(SelectList);
	sizers[0]->Add(StoreNameEntry);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, 2);

	StoreNameLabel = new wxStaticText(this, STATIC_TEXT_StoreNameLabel2, wxT("Store Name: "));
	StoreNameEdit = new wxTextCtrl(this, wxID_ANY, wxT(""));
	nameLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	sizers[1]->Add(StoreNameLabel);
	sizers[1]->Add(StoreNameEdit);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(nameLine);
	mainSizer->Add(0, skipLine);

	orderInfoHeader = new wxStaticText(this, wxID_ANY, wxT("Select order:"));
	orderInfoHeader->SetFont(headerFont);
	sizers[2]->Add(orderInfoHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);

	std::vector<wxString> choices2 = foodPlannerData.getIngredientCategories();
	CategoryEntryLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Categories: "));
	CategoryEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices2.size(), choices2.data());
	sizers[3]->Add(CategoryEntryLabel);
	sizers[3]->Add(CategoryEntry);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, verticalMargin);

	EditCategory = new wxButton(this, wxID_ANY, wxT("Edit Ingredient Category"));
	sizers[8]->Add(frameWidth - EditCategory->GetSize().x - horizontalMargin * 2, 0);
	sizers[8]->Add(EditCategory);
	formatSizer(sizers[8], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[8]);
	mainSizer->Add(0, verticalMargin * 3);

	std::vector<wxString> choices3 = foodPlannerData.getOrder();
	OrderEntryLabel = new wxStaticText(this, wxID_ANY, wxT("Select position: "));
	OrderEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices3.size(), choices3.data());
	sizers[4]->Add(OrderEntryLabel);
	sizers[4]->Add(OrderEntry);
	formatSizer(sizers[4], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[4]);
	mainSizer->Add(0, verticalMargin);

	EnterCategoryInOrder = new wxButton(this, wxID_ANY, wxT("Enter category order"));
	sizers[5]->Add(EnterCategoryInOrder);
	formatSizer(sizers[5], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[5]);
	mainSizer->Add(0, skipLine);

	orderHeader = new wxStaticText(this, wxID_ANY, wxT("Order:"));
	categoryLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	orderHeader->SetFont(headerFont);
	sizers[6]->Add(orderHeader);
	formatSizer(sizers[6], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[6]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(categorySizer);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(categoryLine);
	mainSizer->Add(0, skipLine);

	Delete = new wxButton(this, wxID_ANY, wxT("Delete"));
	Save = new wxButton(this, wxID_ANY, wxT("Save"));
	Exit = new wxButton(this, wxID_ANY, wxT("Exit"));
	sizers[7]->Add(frameWidth - Delete->GetSize().x - Save->GetSize().x - Exit->GetSize().x - 60 - horizontalMargin * 2, 0);
	sizers[7]->Add(Delete);
	sizers[7]->Add(Save);
	sizers[7]->Add(Exit);
	formatSizer(sizers[7], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[7]);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	Exit->Bind(wxEVT_BUTTON, &ListScrollPanel::ExitPressed, this, wxID_ANY);
	boost::function<void(wxCommandEvent&)> deleteFunctor(boost::bind(&ListScrollPanel::DeletePressed, this, _1, test_path));
	Delete->Bind(wxEVT_BUTTON, deleteFunctor, wxID_ANY);
	EditCategory->Bind(wxEVT_BUTTON, &ListScrollPanel::EditCategoryPressed, this, wxID_ANY);
	EnterCategoryInOrder->Bind(wxEVT_BUTTON, &ListScrollPanel::EnterCategoryInOrderPressed, this, wxID_ANY);
	boost::function<void(wxCommandEvent&)> saveFunctor(boost::bind(&ListScrollPanel::SavePressed, this, _1, test_path));
	Save->Bind(wxEVT_BUTTON, saveFunctor, wxID_ANY);
	SelectList->Bind(wxEVT_BUTTON, &ListScrollPanel::SelectListPressed, this, wxID_ANY);

}
ListDialog::ListDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &ListDialog::CloseDialog, this, wxID_ANY);
	Bind(wxEVT_SHOW, &ListDialog::update, this, wxID_ANY);
}

// Private panel functions
void ListScrollPanel::cleanUp() {
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
	StoreNameEdit->SetValue("");
}
void ListScrollPanel::deleteCategoryFromChoiceBox(wxString category) {
	for (int i = 0; i < CategoryEntry->GetCount(); i++) {
		if (category == CategoryEntry->GetString(i)) {
			CategoryEntry->Delete(i);
			break;
		}
	}
}
void ListScrollPanel::deleteOrderFromChoiceBox(wxString order) {
	for (int i = 0; i < OrderEntry->GetCount(); i++) {
		if (order == OrderEntry->GetString(i)) {
			OrderEntry->Delete(i);
			break;
		}
	}
}
void ListScrollPanel::DisplayAndSaveCategoryInOrder(std::string category, std::string order) {
	int index = 0;
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		std::string number = "";
		number = categoryOrderGroups[i].order;
		if (stoi(number) < stoi(order)) {
			index = index + 1;
		}
	}

	categoryOrderGroup group;
	group.orderLabel = new wxStaticText(this, wxID_ANY, order);
	group.categoryLabel = new wxStaticText(this, wxID_ANY, category);
	group.deleteCategory = new wxButton(this, wxID_ANY, wxT("x"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.order = order;
	group.ingredientCategory = category;

	group.newCategorySizer->Add(group.orderLabel);
	group.newCategorySizer->Add(group.categoryLabel);
	group.newCategorySizer->Add(group.deleteCategory);
	
	formatSizer(group.newCategorySizer, 75, frameWidth);

	categorySizer->Insert(index, group.newCategorySizer);

	mainSizer->Layout();

	group.deleteCategory->Bind(wxEVT_BUTTON, &ListScrollPanel::DeleteCategory, this);
	categoryOrderGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void ListScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
int ListScrollPanel::getLongestTextSize(wxChoice* choice) {
	int longestText = 0;
	for (int i = 0; i < choice->GetCount(); i++) {
		if ((choice->GetTextExtent(choice->GetString(i)).x > longestText)) {
			longestText = choice->GetTextExtent(choice->GetString(i)).x;
		}
	}
	return longestText;
}
void ListScrollPanel::insertOrderToChoiceBox(wxString order) {
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
void ListScrollPanel::updateCategories() {
	CategoryEntry->Clear();
	CategoryEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getIngredientCategories()));
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		deleteCategoryFromChoiceBox(categoryOrderGroups[i].ingredientCategory);
	}
	if (CategoryEntry->GetCount() != 0) {
		CategoryEntry->SetSize(CategoryEntry->GetSizeFromTextSize(getLongestTextSize(CategoryEntry), -1));
		sizers[3]->Detach(CategoryEntryLabel);
		sizers[3]->Detach(CategoryEntry);
		sizers[3]->Clear(TRUE);
		sizers[3]->Add(CategoryEntryLabel);
		sizers[3]->Add(CategoryEntry);
		formatSizer(sizers[3], horizontalMargin, frameWidth);
		mainSizer->Layout();
	}
}
void ListScrollPanel::updateListNames() {
	StoreNameEntry->Clear();
	StoreNameEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getListStoreNames()));
	if (StoreNameEntry->GetCount() != 0) {
		StoreNameEntry->SetSize(StoreNameEntry->GetSizeFromTextSize(getLongestTextSize(StoreNameEntry), -1));
		sizers[0]->Detach(SelectList);
		sizers[0]->Detach(StoreNameEntry);
		sizers[0]->Clear(TRUE);
		sizers[0]->Add(SelectList);
		sizers[0]->Add(StoreNameEntry);
		formatSizer(sizers[0], horizontalMargin, frameWidth);
		mainSizer->Layout();
	}
}
void ListScrollPanel::updateOrder() {
	OrderEntry->Clear();
	OrderEntry->Append(foodPlannerData.getOrder());
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		deleteOrderFromChoiceBox(categoryOrderGroups[i].order);
	}
	if (OrderEntry->GetCount() != 0) {
		OrderEntry->SetSize(OrderEntry->GetSizeFromTextSize(getLongestTextSize(OrderEntry), -1));
		sizers[4]->Detach(OrderEntryLabel);
		sizers[4]->Detach(OrderEntry);
		sizers[4]->Clear(TRUE);
		sizers[4]->Add(OrderEntryLabel);
		sizers[4]->Add(OrderEntry);
		formatSizer(sizers[4], horizontalMargin, frameWidth);
		mainSizer->Layout();
	}
}
bool ListScrollPanel::findCategoryInDisplay(std::string category) {
	bool found = false;
	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		if (categoryOrderGroups[i].ingredientCategory == category) {
			found = true;
			break;
		}
	}
	return found;
}
bool ListScrollPanel::findInChoice(std::string name, wxChoice* choice) {
	bool found = false;
	for (int i = 0; i < choice->GetCount(); i++) {
		if (choice->GetString(i) == name) {
			found = true;
			break;
		}
	}
	return found;
}

// Public panel functions
void ListScrollPanel::DeleteCategory(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	std::string category = "";
	wxString order = "";
	long orderValue = 0;
	long values = 0;

	for (int i = 0; i < categoryOrderGroups.size(); i++) {
		if (categoryOrderGroups[i].deleteCategory->GetId() == button) {
			index = i;
			break;
		}
	}

	category = categoryOrderGroups[index].ingredientCategory;
	order = categoryOrderGroups[index].order;

	CategoryEntry->Append(category);

	insertOrderToChoiceBox(order);

	mainSizer->Detach(categoryOrderGroups[index].newCategorySizer);
	categoryOrderGroups[index].newCategorySizer->Clear(TRUE);

	mainSizer->Layout();

	categoryOrderGroups.erase(categoryOrderGroups.begin() + index);
}
void ListScrollPanel::DeletePressed(wxCommandEvent& WXUNUSED(event), std::string test_path) {
	int listIndex = StoreNameEntry->GetSelection();
	if (listIndex != wxNOT_FOUND) {
		foodPlannerData.deleteList(std::string((StoreNameEntry->GetString(listIndex)).mb_str()));
		fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
		cleanUp();
	}
	else {
		wxMessageBox("There is no list currently being edited.");
	}
}
void ListScrollPanel::EditCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
	IngredientCategoriesPanel->DisplayCategories(foodPlannerData.getIngredientCategories());
	IngredientCategoriesWin->ShowModal();
	updateCategories();
	updateOrder();
}
void ListScrollPanel::EnterCategoryInOrderPressed(wxCommandEvent& WXUNUSED(event)) {
	int categoryIndex = CategoryEntry->GetSelection();
	int orderIndex = OrderEntry->GetSelection();

	if ((categoryIndex != wxNOT_FOUND) && (orderIndex != wxNOT_FOUND)) {

		std::string category = std::string((CategoryEntry->GetString(categoryIndex)).mb_str());
		std::string order = std::string((OrderEntry->GetString(orderIndex)).mb_str());

		OrderEntry->Delete(orderIndex);

		CategoryEntry->Delete(categoryIndex);

		DisplayAndSaveCategoryInOrder(category, order);
		OrderEntry->SetSelection(wxNOT_FOUND);
		CategoryEntry->SetSelection(wxNOT_FOUND);
	}
	else {
		wxMessageBox("Enter a category and order.");
	}
}
void ListScrollPanel::ExitPressed(wxCommandEvent& event) {
	ListWin->EndModal(wxCANCEL);
}
void ListScrollPanel::SavePressed(wxCommandEvent& WXUNUSED(event), std::string test_path) {
	bool repeat = false;
	bool addName = true;
	bool newNamePicked = false;
	wxString oldName = "";
	wxString newName = "";
	item.StoreName = std::string((StoreNameEdit->GetValue()).mb_str());
	if ((item.StoreName != "") && (categoryOrderGroups.size() != 0)) {
		for (int i = 0; i < categoryOrderGroups.size(); i++) {
			item.IngredientCategories.push_back(categoryOrderGroups[i].ingredientCategory);
			item.Order.push_back(categoryOrderGroups[i].order);
		}
		if (StoreNameEntry->GetSelection() == wxNOT_FOUND) {
			foodPlannerData.setList(item);
			fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
			cleanUp();
		}
		else {
			oldName = StoreNameEntry->GetString(StoreNameEntry->GetSelection());
			newName = StoreNameEdit->GetValue();
			if (oldName == newName) {
				foodPlannerData.setList(item);
				fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
				cleanUp();
			}
			else if (!foodPlannerData.findList(newName)) {
				foodPlannerData.setListStoreName(std::string(newName.mb_str()), std::string(oldName.mb_str()));
				foodPlannerData.setList(item);
				fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
				cleanUp();
				updateListNames();
			}
			else {
				wxMessageBox(("Store name name is already in use."));
			}
		}
	}
	else {
		wxMessageBox("Pick a store name and fill out at least one ingredient category order pair.");
	}
}
void ListScrollPanel::SelectListPressed(wxCommandEvent& WXUNUSED(event)) {
	int StoreNameIndex = StoreNameEntry->GetSelection();
	List tempItem;
	if (StoreNameIndex != wxNOT_FOUND) {
		std::string storeName = std::string((StoreNameEntry->GetString(StoreNameIndex)).mb_str());
		categorySizer->Clear(TRUE);
		categoryOrderGroups.clear();
		tempItem = foodPlannerData.getList(std::string(StoreNameEntry->GetString(StoreNameIndex).mb_str()));
		for (int i = 0; i < tempItem.IngredientCategories.size(); i++) {
			DisplayAndSaveCategoryInOrder(tempItem.IngredientCategories[i], tempItem.Order[i]);
			deleteOrderFromChoiceBox(tempItem.Order[i]);
			deleteCategoryFromChoiceBox(tempItem.IngredientCategories[i]);
		}
	}
	else {
		wxMessageBox("Select a list.");
	}

}

// Public frame functions
void ListDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	EndModal(wxCANCEL);
}
void ListDialog::update(wxShowEvent& WXUNUSED(event)) {
	if (this->IsShown()) {
		ListPanel->updateCategories();
		ListPanel->updateListNames();
		ListPanel->updateOrder();
	}
}