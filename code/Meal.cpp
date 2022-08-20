#include "Meal.h"
MealDialog* MealWin;
MealScrollPanel* MealPanel;
MealScrollPanel::MealScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, wxScrolledWindow* MainPanel, std::string test_path) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	wxFont headerFont = wxFont(wxFontInfo(12).Bold().Underlined());
	wxFont labelFont = wxFont(wxFontInfo(11).Underlined());
	for (int i = 0; i < 14; i++) {
		horizontalSizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	for (int i = 0; i < 6; i++) {
		verticalSizers[i] = new wxBoxSizer(wxVERTICAL);
	}
	std::vector<wxString> choices;
	choices = foodPlannerData.getMealNames();
	choices = labelOrganizer.alphabetizeVector(choices);
	EnterMeal = new wxButton(this, wxID_ANY, wxT("Edit Meal"));
	SelectMeal = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices.size(), choices.data());
	horizontalSizers[0]->Add(EnterMeal);
	horizontalSizers[0]->Add(SelectMeal);
	formatSizer(horizontalSizers[0], horizontalMargin, frameWidth / 3);
	leftSizer->Add(0, skipLine);
	leftSizer->Add(horizontalSizers[0]);
	leftSizer->Add(0, skipLine);

	MealNameHeader = new wxStaticText(this, wxID_ANY, wxT("Meal Name"));
	MealNameHeader->SetFont(headerFont);
	horizontalSizers[1]->Add(MealNameHeader);
	formatSizer(horizontalSizers[1], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[1]);
	leftSizer->Add(0, skipLine);

	MealNameEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	nameLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(size.x / 3, 2), wxLI_HORIZONTAL);
	horizontalSizers[13]->Add(MealNameEntry);
	formatSizer(horizontalSizers[13], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[13]);
	leftSizer->Add(0, skipLine);
	leftSizer->Add(nameLine);
	leftSizer->Add(0, skipLine);

	CategoryInfoHeader = new wxStaticText(this, wxID_ANY, wxT("Meal Categories Info:"));
	CategoryInfoHeader->SetFont(headerFont);
	horizontalSizers[2]->Add(CategoryInfoHeader);
	formatSizer(horizontalSizers[2], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[2]);
	leftSizer->Add(0, skipLine);

	std::vector<wxString> choices4 = foodPlannerData.getMealCategories();
	choices4 = labelOrganizer.alphabetizeVector(choices4);
	SelectMealCategoriesEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices4.size(), choices4.data());
	horizontalSizers[3]->Add(SelectMealCategoriesEntry);
	formatSizer(horizontalSizers[3], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[3]);
	leftSizer->Add(0, verticalMargin);

	EditMealCategory = new wxButton(this, wxID_ANY, wxT("Add Categories"));
	horizontalSizers[4]->Add(EditMealCategory);
	formatSizer(horizontalSizers[4], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[4]);
	leftSizer->Add(0, skipLine);

	EnterCategory = new wxButton(this, wxID_ANY, wxT("Enter"));
	horizontalSizers[5]->Add(EnterCategory);
	formatSizer(horizontalSizers[5], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[5]);
	leftSizer->Add(0, skipLine);

	CategoryHeader = new wxStaticText(this, wxID_ANY, wxT("Meal Categories:"));
	mealCategoryLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(size.x / 3, 2), wxLI_HORIZONTAL);
	CategoryHeader->SetFont(headerFont);
	horizontalSizers[6]->Add(CategoryHeader);
	formatSizer(horizontalSizers[6], horizontalMargin, frameWidth / 3);
	leftSizer->Add(horizontalSizers[6]);
	leftSizer->Add(0, skipLine);
	leftSizer->Add(categorySizer);
	leftSizer->Add(0, skipLine);
	leftSizer->Add(mealCategoryLine);
	leftSizer->Add(0, skipLine);

	IngredientInfoHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredient Info:"));
	IngredientInfoHeader->SetFont(headerFont);
	horizontalSizers[9]->Add(IngredientInfoHeader);
	formatSizer(horizontalSizers[9], horizontalMargin, frameWidth * (2.0/3.0));
	rightSizer->Add(horizontalSizers[9]);
	rightSizer->Add(0, skipLine);

	IngredientsAmountLabel = new wxStaticText(this, wxID_ANY, wxT("Quantity: "));
	IngredientsAmountLabel->SetFont(labelFont);
	IngredientsAmountEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	verticalSizers[2]->Add(IngredientsAmountLabel, 0, wxALIGN_CENTER);
	verticalSizers[2]->Add(0, verticalMargin);
	verticalSizers[2]->Add(IngredientsAmountEntry, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[2]);

	std::vector<wxString> choices2 = foodPlannerData.getUnits();
	choices2 = labelOrganizer.alphabetizeVector(choices2);
	IngredientsUnitLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Unit of Measurment: "));
	IngredientsUnitLabel->SetFont(labelFont);
	IngredientsUnitEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices2.size(), choices2.data());
	EditUnit = new wxButton(this, wxID_ANY, wxT("Add Units"));
	verticalSizers[1]->Add(IngredientsUnitLabel, 0, wxALIGN_CENTER);
	verticalSizers[1]->Add(0, verticalMargin);
	verticalSizers[1]->Add(IngredientsUnitEntry, 0, wxALIGN_CENTER);
	verticalSizers[1]->Add(0, skipLine);
	verticalSizers[1]->Add(EditUnit, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[1]);

	std::vector<wxString> choices5 = foodPlannerData.getIngredientNames();
	choices5 = labelOrganizer.alphabetizeVector(choices5);
	IngredientsNameLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Name: "));
	IngredientsNameLabel->SetFont(labelFont);
	IngredientsNameEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices5.size(), choices5.data());;
	EditIngredientName = new wxButton(this, wxID_ANY, wxT("Add Ingredient Names"));
	verticalSizers[0]->Add(IngredientsNameLabel, 0, wxALIGN_CENTER);
	verticalSizers[0]->Add(0, verticalMargin);
	verticalSizers[0]->Add(IngredientsNameEntry, 0, wxALIGN_CENTER);
	verticalSizers[0]->Add(0, skipLine);
	verticalSizers[0]->Add(EditIngredientName, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[0]);

	std::vector<wxString> choices3 = foodPlannerData.getIngredientCategories();
	choices3 = labelOrganizer.alphabetizeVector(choices3);
	IngredientsStoreCategoryLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Store Category:"));
	IngredientsStoreCategoryLabel->SetFont(labelFont);
	IngredientsStoreCategoryEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices3.size(), choices3.data());
	EditIngredientStoreCategory = new wxButton(this, wxID_ANY, wxT("Add Categories"));
	verticalSizers[3]->Add(IngredientsStoreCategoryLabel, 0, wxALIGN_CENTER);
	verticalSizers[3]->Add(0, verticalMargin);
	verticalSizers[3]->Add(IngredientsStoreCategoryEntry, 0, wxALIGN_CENTER);
	verticalSizers[3]->Add(0, skipLine);
	verticalSizers[3]->Add(EditIngredientStoreCategory, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[3]);

	std::vector<wxString> choices6 = foodPlannerData.getPantryCategories();
	choices6 = labelOrganizer.alphabetizeVector(choices6);
	IngredientsPantryCategoryLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Pantry Category:"));
	IngredientsPantryCategoryLabel->SetFont(labelFont);
	IngredientsPantryCategoryEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices6.size(), choices6.data());
	EditIngredientPantryCategory = new wxButton(this, wxID_ANY, wxT("Add Categories"));
	verticalSizers[5]->Add(IngredientsPantryCategoryLabel, 0, wxALIGN_CENTER);
	verticalSizers[5]->Add(0, verticalMargin);
	verticalSizers[5]->Add(IngredientsPantryCategoryEntry, 0, wxALIGN_CENTER);
	verticalSizers[5]->Add(0, skipLine);
	verticalSizers[5]->Add(EditIngredientPantryCategory, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[5]);

	EnterIngredient = new wxButton(this, wxID_ANY, wxT("Enter"));
	verticalSizers[4]->Add(0, skipLine);
	verticalSizers[4]->Add(0, verticalMargin);
	verticalSizers[4]->Add(EnterIngredient, 0, wxALIGN_CENTER);
	horizontalSizers[10]->Add(horizontalMargin, 0);
	horizontalSizers[10]->Add(verticalSizers[4]);

	rightSizer->Add(horizontalSizers[10]);
	rightSizer->Add(0, verticalMargin);
	
	IngredientHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredients:"));
	IngredientLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(size.x * (2.0/3.0), 2), wxLI_HORIZONTAL);
	IngredientHeader->SetFont(headerFont);
	horizontalSizers[12]->Add(IngredientHeader);
	formatSizer(horizontalSizers[12], horizontalMargin, frameWidth * (2.0 / 3.0));
	rightSizer->Add(horizontalSizers[12]);
	rightSizer->Add(0, skipLine);
	rightSizer->Add(ingredientSizer);
	rightSizer->Add(0, skipLine);
	rightSizer->Add(IngredientLine);
	rightSizer->Add(0, skipLine);

	Clear = new wxButton(this, wxID_ANY, wxT("Clear"));
	Delete = new wxButton(this, wxID_ANY, wxT("Delete"));
	Save = new wxButton(this, wxID_ANY, wxT("Save"));
	Exit = new wxButton(this, wxID_ANY, wxT("Exit"));
	horizontalSizers[7]->Add((frameWidth * (2.0 / 3.0)) - Delete->GetSize().x - Save->GetSize().x - Exit->GetSize().x - Clear->GetSize().x - 80 - horizontalMargin * 2, 0);
	horizontalSizers[7]->Add(Clear);
	horizontalSizers[7]->Add(Delete);
	horizontalSizers[7]->Add(Save);
	horizontalSizers[7]->Add(Exit);
	formatSizer(horizontalSizers[7], horizontalMargin, frameWidth * (2.0/3.0));
	rightSizer->Add(horizontalSizers[7]);
	rightSizer->Add(0, skipLine);

	centerLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(2, size.y *1.2), wxLI_VERTICAL);
	mainSizer->Add(leftSizer);
	mainSizer->Add(centerLine);
	mainSizer->Add(rightSizer);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	IngredientNamesWin = new IngredientNamesDialog(wxT("Ingredient Names"), wxDefaultPosition, wxSize(400, 400));
	IngredientNamesPanel = new IngredientNamesScrollPanel(IngredientNamesWin, wxID_ANY, wxSize(400, 400), test_path);
	
	IngredientCategoriesWin = new IngredientCategoriesDialog(wxT("Ingredient Categories"), wxDefaultPosition, wxSize(400, 400));
	IngredientCategoriesPanel = new IngredientCategoriesScrollPanel(IngredientCategoriesWin, wxID_ANY, wxSize(400, 400), test_path);

	UnitsWin = new UnitsDialog(wxT("Units"), wxDefaultPosition, wxSize(400, 400));
	UnitsPanel = new UnitsScrollPanel(UnitsWin, wxID_ANY, wxSize(400, 400), test_path);

	MealCategoriesWin = new MealCategoriesDialog(wxT("Meal Categories"), wxDefaultPosition, wxSize(400, 400));
	MealCategoriesPanel = new MealCategoriesScrollPanel(MealCategoriesWin, wxID_ANY, MealCategoriesWin->GetSize(), test_path);

	PantryCategoriesWin = new PantryCategoriesDialog(wxT("Pantry Categories"), wxDefaultPosition, wxSize(400, 400));
	PantryCategoriesPanel = new PantryCategoriesScrollPanel(PantryCategoriesWin, wxID_ANY, PantryCategoriesWin->GetSize(), test_path);

	Clear->Bind(wxEVT_BUTTON, &MealScrollPanel::ClearPressed, this, wxID_ANY);
	EditIngredientStoreCategory->Bind(wxEVT_BUTTON, &MealScrollPanel::EditIngredientStoreCategoryPressed, this, wxID_ANY);
	EditIngredientPantryCategory->Bind(wxEVT_BUTTON, &MealScrollPanel::EditIngredientPantryCategoryPressed, this, wxID_ANY);
	EditMealCategory->Bind(wxEVT_BUTTON, &MealScrollPanel::EditMealCategoryPressed, this, wxID_ANY);
	EditIngredientName->Bind(wxEVT_BUTTON, &MealScrollPanel::EditIngredientNamePressed, this, wxID_ANY);
	EditUnit->Bind(wxEVT_BUTTON, &MealScrollPanel::EditUnitPressed, this, wxID_ANY);
	EnterCategory->Bind(wxEVT_BUTTON, &MealScrollPanel::EnterCategoryPressed, this, wxID_ANY);
	EnterIngredient->Bind(wxEVT_BUTTON, &MealScrollPanel::EnterIngredientPressed, this, wxID_ANY);
	EnterMeal->Bind(wxEVT_BUTTON, &MealScrollPanel::EnterMealPressed, this, wxID_ANY);
	Exit->Bind(wxEVT_BUTTON, &MealScrollPanel::ExitPressed, this, wxID_ANY);
	boost::function<void(wxCommandEvent&)> deleteFunctor(boost::bind(&MealScrollPanel::DeletePressed, this, _1, test_path));
	Delete->Bind(wxEVT_BUTTON, deleteFunctor, wxID_ANY);
	boost::function<void(wxCommandEvent&)> saveFunctor(boost::bind(&MealScrollPanel::SavePressed, this, _1, test_path));
	Save->Bind(wxEVT_BUTTON, saveFunctor, wxID_ANY);
	
}
MealDialog::MealDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size) {
	this->Bind(wxEVT_SHOW, &MealDialog::update, this, wxID_ANY);
}

// Private panel functions
bool MealScrollPanel::findMealCategoryInDisplay(std::string name) {
	bool found = false;
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		if (displayCategoryInfoGroups[i].category == name) {
			found = true;
			break;
		}
	}
	return found;
}
bool MealScrollPanel::findInChoice(std::string name, wxChoice* choice) {
	bool found = false;
	for (int i = 0; i < choice->GetCount(); i++) {
		if (choice->GetString(i) == name) {
			found = true;
			break;
		}
	}
	return found;
}
bool MealScrollPanel::findIngredientInDisplay(std::string name) {
	bool found = false;
	for (int i = 0; i < displayIngredientInfoGroups.size(); i++) {
		if (displayIngredientInfoGroups[i].ingredient.Name == name) {
			found = true;
			break;
		}
	}
	return found;
}
void MealScrollPanel::cleanUp() {
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		SelectMealCategoriesEntry->Append(displayCategoryInfoGroups[i].category);
	}
	ingredientSizer->Clear(TRUE);
	categorySizer->Clear(TRUE);
	mainSizer->Layout();
	displayCategoryInfoGroups.clear();
	displayIngredientInfoGroups.clear();
	meal.Name = "";
	meal.Categories.clear();
	meal.Ingredients.clear();
	MealNameEntry->SetValue("");
	IngredientsNameEntry->SetSelection(wxNOT_FOUND);
	IngredientsAmountEntry->SetValue("");
	IngredientsUnitEntry->SetSelection(wxNOT_FOUND);
	IngredientsStoreCategoryEntry->SetSelection(wxNOT_FOUND);
	IngredientsNameEntry->SetSelection(wxNOT_FOUND);
	SelectMeal->SetSelection(wxNOT_FOUND);
	SelectMealCategoriesEntry->SetSelection(wxNOT_FOUND);

	this->FitInside();
	this->SetScrollRate(5, 5);

}
bool MealScrollPanel::checkIfNumber(std::string str) {
	bool isNumber = true;
	int decimal = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.') {
			decimal++;
		}
		if ((isdigit(str[i]) == false) && (decimal != 1)) {
			isNumber = false;
			break;
		}
	}
	return isNumber;
}
void MealScrollPanel::DeleteCategoryFromChoiceBox(std::string category) {
	for (int i = 0; i < SelectMealCategoriesEntry->GetCount(); i++) {
		if (SelectMealCategoriesEntry->GetString(i) == category) {
			SelectMealCategoriesEntry->Delete(i);
			break;
		}
	}
}
void MealScrollPanel::DisplayAndSaveCategory(std::string category) {
	displayCategoryInfoGroup group;
	group.categoryLabel = new wxStaticText(this, wxID_ANY, category);
	group.deleteCategory = new wxButton(this, wxID_ANY, wxT("x"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.category = category;

	group.newCategorySizer->Add(group.categoryLabel, 0);
	group.newCategorySizer->Add(group.deleteCategory, 0);
	group.spacer->Add(0, 2);

	formatSizer(group.newCategorySizer, 100, frameWidth / 3);
	
	categorySizer->Add(group.newCategorySizer);
	categorySizer->Add(group.spacer);

	mainSizer->Layout();

	group.deleteCategory->Bind(wxEVT_BUTTON, &MealScrollPanel::DeleteCategory, this);
	displayCategoryInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::DisplayAndSaveIngredient(Ingredient item) {
	displayIngredientInfoGroup group;
	group.deleteIngredient = new wxButton(this, wxID_ANY, wxT("x"));
	group.ingredientLabel = new wxStaticText(this, wxID_ANY, round(item.Amount, 3) + " " + item.Unit + " " + item.Name + "    Store Category: " + item.storeCategory + "    Pantry Category: " + item.pantryCategory);
	group.newIngredientSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.ingredient = item;

	group.newIngredientSizer->Add(group.ingredientLabel, 0);
	group.newIngredientSizer->Add(group.deleteIngredient, 0);
	group.spacer->Add(0, 2);

	formatSizer(group.newIngredientSizer, 150, frameWidth * (2.0/3.0));
	ingredientSizer->Add(group.newIngredientSizer);
	ingredientSizer->Add(group.spacer);

	mainSizer->Layout();

	group.deleteIngredient->Bind(wxEVT_BUTTON, &MealScrollPanel::DeleteIngredient, this);

	displayIngredientInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth) {
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
int MealScrollPanel::getLongestTextSize(wxChoice* choice) {
	int longestText = 0;
	for (int i = 0; i < choice->GetCount(); i++) {
		if ((choice->GetTextExtent(choice->GetString(i)).x > longestText)) {
			longestText = choice->GetTextExtent(choice->GetString(i)).x;
		}
	}
	return longestText;
}
std::string MealScrollPanel::round(double num, int decimalPlaces) {
	std::string numStr = std::to_string(num);
	std::string label;
	int endSignal = 0;
	for (int i = 0; i < numStr.length(); i++) {
		label = label + numStr[i];
		if (endSignal) {
			endSignal++;
			if ((endSignal - 1) == decimalPlaces) {
				break;
			}
		}
		if (numStr[i] == '.') {
			endSignal = 1;
		}
	}
	return label;
}
void MealScrollPanel::updateIngredientStoreCategories() {
	IngredientsStoreCategoryEntry->Clear();
	IngredientsStoreCategoryEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getIngredientCategories()));
	if (IngredientsStoreCategoryEntry->GetCount() != 0) {
		IngredientsStoreCategoryEntry->SetSize(IngredientsStoreCategoryEntry->GetSizeFromTextSize(getLongestTextSize(IngredientsStoreCategoryEntry), -1));
		mainSizer->Layout();
	}
}
void MealScrollPanel::updateIngredientPantryCategories() {
	IngredientsPantryCategoryEntry->Clear();
	IngredientsPantryCategoryEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getPantryCategories()));
	if (IngredientsPantryCategoryEntry->GetCount() != 0) {
		IngredientsPantryCategoryEntry->SetSize(IngredientsPantryCategoryEntry->GetSizeFromTextSize(getLongestTextSize(IngredientsPantryCategoryEntry), -1));
		mainSizer->Layout();
	}
}
void MealScrollPanel::updateIngredientNames() {
	IngredientsNameEntry->Clear();
	IngredientsNameEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getIngredientNames()));
	if (IngredientsNameEntry->GetCount() != 0) {
		IngredientsNameEntry->SetSize(IngredientsNameEntry->GetSizeFromTextSize(getLongestTextSize(IngredientsNameEntry), -1));
		mainSizer->Layout();
	}
}
void MealScrollPanel::updateMealCategories() {
	SelectMealCategoriesEntry->Clear();
	SelectMealCategoriesEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getMealCategories()));
	if (SelectMealCategoriesEntry->GetCount() != 0) {
		SelectMealCategoriesEntry->SetSize(SelectMealCategoriesEntry->GetSizeFromTextSize(getLongestTextSize(SelectMealCategoriesEntry), -1));
		mainSizer->Layout();
	}
}
void MealScrollPanel::updateMealNames() {
	SelectMeal->Clear();
	SelectMeal->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getMealNames()));
	if (SelectMeal->GetCount() != 0) {
		SelectMeal->SetSize(SelectMeal->GetSizeFromTextSize(getLongestTextSize(SelectMeal), -1));
		horizontalSizers[0]->Detach(EnterMeal);
		horizontalSizers[0]->Detach(SelectMeal);
		horizontalSizers[0]->Clear(TRUE);
		horizontalSizers[0]->Add(EnterMeal);
		horizontalSizers[0]->Add(SelectMeal);
		formatSizer(horizontalSizers[0], horizontalMargin, frameWidth / 3);
		mainSizer->Layout();
	}
}
void MealScrollPanel::updateUnits() {
	IngredientsUnitEntry->Clear();
	IngredientsUnitEntry->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getUnits()));
	if (IngredientsUnitEntry->GetCount() != 0) {
		IngredientsUnitEntry->SetSize(IngredientsUnitEntry->GetSizeFromTextSize(getLongestTextSize(IngredientsUnitEntry), -1));
		mainSizer->Layout();
	}
}

// Public panel functions
void MealScrollPanel::ClearPressed(wxCommandEvent& WXUNUSED(event)) {
	cleanUp();
}
void MealScrollPanel::EditIngredientPantryCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
	PantryCategoriesPanel->DisplayCategories(foodPlannerData.getPantryCategories());
	PantryCategoriesWin->ShowModal();
	updateIngredientPantryCategories();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::EditIngredientStoreCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
	IngredientCategoriesPanel->DisplayCategories(foodPlannerData.getIngredientCategories());
	IngredientCategoriesWin->ShowModal();
	updateIngredientStoreCategories();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::EditIngredientNamePressed(wxCommandEvent& WXUNUSED(event)) {
	IngredientNamesPanel->DisplayIngredientNames(foodPlannerData.getIngredientNames());
	IngredientNamesWin->ShowModal();
	updateIngredientNames();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::EditMealCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
	MealCategoriesPanel->DisplayCategories(foodPlannerData.getMealCategories());
	MealCategoriesWin->ShowModal();
	updateMealCategories();
	this->FitInside();
	this->SetScrollRate(5, 5);

}
void MealScrollPanel::EditUnitPressed(wxCommandEvent& WXUNUSED(event)) {
	UnitsPanel->DisplayUnits(foodPlannerData.getUnits());
	UnitsWin->ShowModal();
	updateUnits();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::EnterCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
	std::string category = "";
	int categoryIndex = SelectMealCategoriesEntry->GetSelection();
	if ((categoryIndex != wxNOT_FOUND)) {
		category = SelectMealCategoriesEntry->GetString(categoryIndex);
		DisplayAndSaveCategory(category);
		SelectMealCategoriesEntry->Delete(categoryIndex);
	}
	else {
		wxMessageBox("Pick a category.");
	}
}
void MealScrollPanel::EnterIngredientPressed(wxCommandEvent& WXUNUSED(event)) {
	Ingredient item;
	int unitIndex = 0;
	int storeCategoryIndex = 0;
	int nameIndex = 0;
	int pantryCategoryIndex = 0;
	std::string checkNumber = std::string(IngredientsAmountEntry->GetValue().mb_str());
	nameIndex = IngredientsNameEntry->GetSelection();
	unitIndex = IngredientsUnitEntry->GetSelection();
	storeCategoryIndex = IngredientsStoreCategoryEntry->GetSelection();
	pantryCategoryIndex = IngredientsPantryCategoryEntry->GetSelection();

	if (checkIfNumber(checkNumber)) {
		(IngredientsAmountEntry->GetValue()).ToDouble(&item.Amount);
		if ((nameIndex != wxNOT_FOUND) && (unitIndex != wxNOT_FOUND) && (item.Amount != 0) && (storeCategoryIndex != wxNOT_FOUND) && (pantryCategoryIndex != wxNOT_FOUND)) {
			if (inputValid(std::string(IngredientsAmountEntry->GetValue().mb_str()))) {
				item.Unit = IngredientsUnitEntry->GetString(unitIndex);
				item.storeCategory = IngredientsStoreCategoryEntry->GetString(storeCategoryIndex);
				item.pantryCategory = IngredientsPantryCategoryEntry->GetString(pantryCategoryIndex);
				item.Name = IngredientsNameEntry->GetString(nameIndex);
				IngredientsNameEntry->SetSelection(wxNOT_FOUND);
				IngredientsStoreCategoryEntry->SetSelection(wxNOT_FOUND);
				IngredientsUnitEntry->SetSelection(wxNOT_FOUND);
				IngredientsAmountEntry->SetValue("");
				IngredientsPantryCategoryEntry->SetSelection(wxNOT_FOUND);
				DisplayAndSaveIngredient(item);
			}
			else {
				wxMessageBox(wxT("Invalid character used."));
			}
		}
		else {
			wxMessageBox(wxT("All ingredient fields must be filled out"));
		}
	}
	else {
		wxMessageBox("Amount must be a number.");
	}
	

}
void MealScrollPanel::EnterMealPressed(wxCommandEvent& WXUNUSED(event)) {
	int selectedMealIndex = SelectMeal->GetSelection();
	if (selectedMealIndex != wxNOT_FOUND) {
		cleanUp();
		updateMealCategories();
		Meal tempMeal = foodPlannerData.getMeal(std::string(SelectMeal->GetString(selectedMealIndex).mb_str()));
		MealNameEntry->SetValue(tempMeal.Name);
		for (int i = 0; i < tempMeal.Ingredients.size(); i++) {
			DisplayAndSaveIngredient(tempMeal.Ingredients[i]);
		}
		for (int i = 0; i < tempMeal.Categories.size(); i++) {
			DisplayAndSaveCategory(tempMeal.Categories[i]);
			DeleteCategoryFromChoiceBox(tempMeal.Categories[i]);
		}
	}
	else {
		wxMessageBox("Select a Meal.");
	}
}
void MealScrollPanel::ExitPressed(wxCommandEvent& WXUNUSED(event)) {
	MealWin->EndModal(wxCANCEL);
}
void MealScrollPanel::DeleteCategory(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		if (displayCategoryInfoGroups[i].deleteCategory->GetId() == button) {
			index = i;
			break;
		}
	}
	SelectMealCategoriesEntry->Append(displayCategoryInfoGroups[index].category);
	displayCategoryInfoGroups[index].newCategorySizer->Clear(TRUE);
	displayCategoryInfoGroups[index].spacer->Clear(TRUE);
	mainSizer->Layout();
	displayCategoryInfoGroups.erase(displayCategoryInfoGroups.begin() + index);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::DeleteIngredient(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayIngredientInfoGroups.size(); i++) {
		if (displayIngredientInfoGroups[i].deleteIngredient->GetId() == button) {
			index = i;
			break;
		}
	}
	displayIngredientInfoGroups[index].newIngredientSizer->Clear(TRUE);
	displayIngredientInfoGroups[index].spacer->Clear(TRUE);
	mainSizer->Layout();
	displayIngredientInfoGroups.erase(displayIngredientInfoGroups.begin() + index);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealScrollPanel::DeletePressed(wxCommandEvent& WXUNUSED(event), std::string test_path) {
	int mealIndex = SelectMeal->GetSelection();
	if (mealIndex != wxNOT_FOUND) {
		foodPlannerData.deleteMeal(std::string((SelectMeal->GetString(mealIndex)).mb_str()));
		fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
		cleanUp();
		updateMealNames();
		SelectMeal->SetSelection(mealIndex);
	}
	else {
		wxMessageBox("There is no meal currently being edited.");
	}
}
void MealScrollPanel::SavePressed(wxCommandEvent& WXUNUSED(event), std::string test_path) {
	bool repeat = false;
	bool addName = true;
	bool newNamePicked = false;
	wxString oldName = "";
	wxString newName = "";
	meal.Name = std::string((MealNameEntry->GetValue()).mb_str());
	if (inputValid(meal.Name)) {
		if ((meal.Name != "") && (displayCategoryInfoGroups.size() != 0) && (displayIngredientInfoGroups.size() != 0)) {
			for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
				meal.Categories.push_back(displayCategoryInfoGroups[i].category);
			}
			for (int i = 0; i < displayIngredientInfoGroups.size(); i++) {
				meal.Ingredients.push_back(displayIngredientInfoGroups[i].ingredient);
			}
			if (SelectMeal->GetSelection() == wxNOT_FOUND) {
				foodPlannerData.setMeal(meal);
				fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
				cleanUp();
				updateMealNames();
			}
			else {
				oldName = SelectMeal->GetString(SelectMeal->GetSelection());
				newName = MealNameEntry->GetValue();
				if (oldName == newName) {
					foodPlannerData.setMeal(meal);
					fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
					cleanUp();
					updateMealNames();
				}
				else if (!foodPlannerData.findMeal(newName)) {
					foodPlannerData.setMealName(std::string(newName.mb_str()), std::string(oldName.mb_str()));
					foodPlannerData.setMeal(meal);
					fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
					cleanUp();
					updateMealNames();
				}
				else {
					wxMessageBox(("Meal name is already in use."));
				}
			}
		}
		else {
			wxMessageBox("Pick a meal and fill out at least one ingredient and one meal category.");
		}
	}
	else {
		wxMessageBox("Invalid character for meal name used.");
	}
	
}
void MealDialog::update(wxShowEvent& event) {
	if (this->IsShown()) {
		MealPanel->updateIngredientStoreCategories();
		MealPanel->updateIngredientPantryCategories();
		MealPanel->updateIngredientNames();
		MealPanel->updateMealCategories();
		MealPanel->updateMealNames();
		MealPanel->updateUnits();
	}
}

// Public frame functions
void MealDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	EndModal(wxCANCEL);
}
