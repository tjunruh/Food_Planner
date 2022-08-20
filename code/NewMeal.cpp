#include "NewMeal.h"

NewMealScrollPanel::NewMealScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, SavedInfo save, JSON infoHandler) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	const int skipLine = 20;
	const int verticalMargin = 2;
	const int horizontalMargin = 50;
	wxBoxSizer* sizers[12] = {};
	for (int i = 0; i < 12; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	mainSizer->Add(0, skipLine);
	MealNameLabel = new wxStaticText(this, wxID_ANY, wxT("Meal Name:"));
	MealNameEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[0]->Add(MealNameLabel, 0);
	sizers[0]->Add(MealNameEntry, 0);
	formatSizer(sizers[0], horizontalMargin, size.x);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	IngredientInfoHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredient Info:"));
	sizers[1]->Add(IngredientInfoHeader, 0);
	formatSizer(sizers[1], horizontalMargin, size.x);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	IngredientsNameLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Name: "));
	IngredientsNameEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[2]->Add(IngredientsNameLabel, 0);
	sizers[2]->Add(IngredientsNameEntry, 0);
	formatSizer(sizers[2], horizontalMargin, size.x);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, verticalMargin);

	wxString UnitsOfMeasurement[3] = { "Cups", "Teaspoons", "Tablespoons" };
	IngredientsUnitLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Unit of Measurement: "));
	IngredientsUnitEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, UnitsOfMeasurement);
	sizers[3]->Add(IngredientsUnitLabel, 0);
	sizers[3]->Add(IngredientsUnitEntry, 0);
	formatSizer(sizers[3], horizontalMargin, size.x);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, verticalMargin);

	IngredientsAmountLabel = new wxStaticText(this, wxID_ANY, wxT("Quantity: "));
	IngredientsAmountEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[4]->Add(IngredientsAmountLabel, 0);
	sizers[4]->Add(IngredientsAmountEntry, 0);
	formatSizer(sizers[4], horizontalMargin, size.x);
	mainSizer->Add(sizers[4]);
	mainSizer->Add(0, verticalMargin);

	std::vector<wxString> choices;
	choices = infoHandler.GetAvailableIngredientCategories(save);
	IngredientsCategoryLabel = new wxStaticText(this, wxID_ANY, wxT("Ingredient Category: "));
	IngredientsCategoryEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices.size(), choices.data());
	sizers[5]->Add(IngredientsCategoryLabel, 0);
	sizers[5]->Add(IngredientsCategoryEntry, 0);
	formatSizer(sizers[5], horizontalMargin, size.x);
	mainSizer->Add(sizers[5]);
	mainSizer->Add(0, verticalMargin);

	EnterIngredient = new wxButton(this, wxID_ANY, wxT("Save Ingredient"));
	sizers[6]->Add(EnterIngredient);
	formatSizer(sizers[6], horizontalMargin, size.x);
	mainSizer->Add(sizers[6], 0);
	mainSizer->Add(0, skipLine);

	IngredientHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredients:"));
	sizers[7]->Add(IngredientHeader, 0);
	formatSizer(sizers[7], horizontalMargin, size.x);
	mainSizer->Add(sizers[7]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(ingredientSizer);
	mainSizer->Add(0, skipLine);

	CategoryInfoHeader = new wxStaticText(this, wxID_ANY, wxT("Categorization Info:"));
	sizers[8]->Add(CategoryInfoHeader, 0);
	formatSizer(sizers[8], horizontalMargin, size.x);
	mainSizer->Add(sizers[8]);
	mainSizer->Add(0, verticalMargin);

	std::vector<wxString> choices2;
	choices2 = infoHandler.GetAvailableMealCategories(save);
	SelectMealCategoriesEntry = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices2.size(), choices2.data());
	EnterCategory = new wxButton(this, wxID_ANY, wxT("Enter Category"));
	sizers[9]->Add(SelectMealCategoriesEntry, 0);
	sizers[9]->Add(EnterCategory, 0);
	formatSizer(sizers[9], horizontalMargin, size.x);
	mainSizer->Add(sizers[9]);
	mainSizer->Add(0, skipLine);

	CategoryHeader = new wxStaticText(this, wxID_ANY, wxT("Categories:"));
	sizers[10]->Add(CategoryHeader, 0);
	formatSizer(sizers[10], horizontalMargin, size.x);
	mainSizer->Add(sizers[10]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(categorySizer);
	mainSizer->Add(0, skipLine);

	Cancel = new wxButton(this, BUTTON_Cancel, wxT("Cancel"));
	Ok = new wxButton(this, BUTTON_Ok, wxT("Ok"));
	sizers[11]->Add((size.x - Cancel->GetSize().x - Ok->GetSize().x) / 2, 0);
	sizers[11]->Add(Cancel, 0);
	sizers[11]->Add(Ok, 0);
	sizers[11]->Add((size.x - Cancel->GetSize().x - Ok->GetSize().x) / 2, 0);
	mainSizer->Add(sizers[11]);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
NewMealFrame::NewMealFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame*)NULL, -1, title, pos, size)
{
	
}

// NewMealFrame functions
void NewMealScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void NewMealScrollPanel::cleanUp() {
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		SelectMealCategoriesEntry->Append(displayCategoryInfoGroups[i].category);
	}
	ingredientSizer->Clear(TRUE);
	categorySizer->Clear(TRUE);
	displayCategoryInfoGroups.clear();
	displayIngredientInfoGroups.clear();
	meal.Name = "";
	meal.Categories.clear();
	meal.Ingredients.clear();
	MealNameEntry->SetValue("");
	IngredientsNameEntry->SetValue("");
	IngredientsAmountEntry->SetValue("");
}
void NewMealScrollPanel::EnterIngredientPressed(wxCommandEvent& WXUNUSED(event)) {
	Ingredient item;
	int unitIndex = 0;
	int categoryIndex = 0;
	item.Name = std::string((IngredientsNameEntry->GetValue()).mb_str());
	unitIndex = IngredientsUnitEntry->GetSelection();
	categoryIndex = IngredientsCategoryEntry->GetSelection();
	(IngredientsAmountEntry->GetValue()).ToDouble(&item.Amount);

	if ((item.Name != "") && (unitIndex != wxNOT_FOUND) && (item.Amount != 0) && (categoryIndex != wxNOT_FOUND)) {
		item.Unit = IngredientsUnitEntry->GetString(unitIndex);
		item.Category = IngredientsCategoryEntry->GetString(categoryIndex);
		IngredientsNameEntry->SetValue("");
		IngredientsAmountEntry->SetValue("");
		DisplayAndSaveIngredient(item);
	}
	else {
		wxMessageBox(wxT("All ingredient fields must be filled out"));
	}
}
void NewMealScrollPanel::EnterCategoryPressed(wxCommandEvent& WXUNUSED(event)) {
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
void NewMealScrollPanel::CancelPressed(wxCommandEvent& WXUNUSED(event)) {
	cleanUp();
}
void NewMealScrollPanel::OkPressed(wxCommandEvent& WXUNUSED(event), SavedInfo save, JSON infoHandler, std::string saved_info_path) {
	meal.Name = std::string((MealNameEntry->GetValue()).mb_str());
	if (meal.Name != "") {
		for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
			meal.Categories.push_back(displayCategoryInfoGroups[i].category);
		}
		for (int i = 0; i < displayIngredientInfoGroups.size(); i++) {
			meal.Ingredients.push_back(displayIngredientInfoGroups[i].ingredient);
		}
		save = infoHandler.setMeal(save, meal);
		infoHandler.write_file(saved_info_path, infoHandler.Stringify(save));
		cleanUp();
	}
	else {
		wxMessageBox("Meal name must be filled out.");
	}

}
void NewMealFrame::CloseFrame(wxCloseEvent& WXUNUSED(event), wxFrame* MainWin) {
	MainWin->SetPosition(GetPosition());
	MainWin->SetSize(GetSize());
	Show(FALSE);
	MainWin->Show(TRUE);
}
void NewMealScrollPanel::DeleteCategory(wxCommandEvent& event) {
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

}
void NewMealScrollPanel::DeleteIngredient(wxCommandEvent& event) {
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
}
void NewMealScrollPanel::DisplayAndSaveCategory(std::string category) {
	displayCategoryInfoGroup group;
	group.categoryLabel = new wxStaticText(this, wxID_ANY, category);
	group.deleteCategory = new wxButton(this, wxID_ANY, wxT("x"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.category = category;

	group.newCategorySizer->Add(group.categoryLabel, 0);
	group.newCategorySizer->Add(group.deleteCategory, 0);
	group.spacer->Add(0, 2);
	formatSizer(group.newCategorySizer, 100, frameWidth);
	categorySizer->Add(group.newCategorySizer);
	categorySizer->Add(0, 2);

	mainSizer->Layout();

	group.deleteCategory->Bind(wxEVT_BUTTON, &NewMealScrollPanel::DeleteCategory, this);
	displayCategoryInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void NewMealScrollPanel::DisplayAndSaveIngredient(Ingredient item) {
	displayIngredientInfoGroup group;
	group.deleteIngredient = new wxButton(this, wxID_ANY, wxT("x"));
	group.ingredientLabel = new wxStaticText(this, wxID_ANY, std::to_string(int(round(item.Amount * 100.0) / 100)) + " " + item.Unit + " " + item.Name + "    Category: " + item.Category);
	group.newIngredientSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.ingredient = item;

	group.newIngredientSizer->Add(group.ingredientLabel, 0);
	group.newIngredientSizer->Add(group.deleteIngredient, 0);
	group.spacer->Add(0, 2);
	formatSizer(group.newIngredientSizer, 50, frameWidth);
	ingredientSizer->Add(group.newIngredientSizer);
	ingredientSizer->Add(group.spacer);
	mainSizer->Layout();

	group.deleteIngredient->Bind(wxEVT_BUTTON, &NewMealScrollPanel::DeleteIngredient, this);
	displayIngredientInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}

