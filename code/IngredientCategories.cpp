#include "IngredientCategories.h"

IngredientCategoriesDialog* IngredientCategoriesWin;
IngredientCategoriesScrollPanel* IngredientCategoriesPanel;

IngredientCategoriesScrollPanel::IngredientCategoriesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;

	for (int i = 0; i < 3; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}

	mainSizer->Add(0, skipLine);

	Directions = new wxStaticText(this, wxID_ANY, wxT("Type category and press enter."));
	sizers[0]->Add(Directions);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	IngredientCategoryEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[1]->Add(IngredientCategoryEntry);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	ingredientHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredient Categories:"));
	sizers[2]->Add(ingredientHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(ingredientSizer);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	boost::function<void(wxCommandEvent&)> enterCategoryFunctor(boost::bind(&IngredientCategoriesScrollPanel::EnterIngredientCategory, this, _1, saved_info_path));
	IngredientCategoryEntry->Bind(wxEVT_TEXT_ENTER, enterCategoryFunctor, wxID_ANY);
}
IngredientCategoriesDialog::IngredientCategoriesDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &IngredientCategoriesDialog::CloseDialog, this, wxID_ANY);
}

// Private panel functions
void IngredientCategoriesScrollPanel::cleanUp() {
	IngredientCategoryEntry->SetValue("");
	ingredientSizer->Clear(TRUE);
	displayInfoGroups.clear();
}
void IngredientCategoriesScrollPanel::DisplayCategory(std::string category) {
	displayInfoGroup group;
	group.categoryLabel = new wxStaticText(this, wxID_ANY, category);
	group.deleteCategory = new wxButton(this, wxID_ANY, wxT("Rename"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.category = category;

	group.newCategorySizer->Add(group.categoryLabel);
	group.newCategorySizer->Add(group.deleteCategory);
	group.spacer->Add(0, 2);

	formatSizer(group.newCategorySizer, horizontalMargin, frameWidth);

	ingredientSizer->Add(group.newCategorySizer);
	ingredientSizer->Add(group.spacer);

	mainSizer->Layout();

	group.deleteCategory->Bind(wxEVT_BUTTON, &IngredientCategoriesScrollPanel::RenameCategory, this);
	displayInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void IngredientCategoriesScrollPanel::DisplayCategories(std::vector<wxString> categories) {
	categories = labelOrganizer.alphabetizeVector(categories);
	for (int i = 0; i < categories.size(); i++) {
		DisplayCategory(std::string(categories[i].mb_str()));
	}
}
void IngredientCategoriesScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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

// Public panel functions
void IngredientCategoriesScrollPanel::RenameCategory(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		if (displayInfoGroups[i].deleteCategory->GetId() == button) {
			index = i;
			break;
		}
	}
	renameDataPanel->setUp(renameDataPanel->ingredientStoreCategories, displayInfoGroups[index].category);
	renameDataWin->ShowModal();
	cleanUp();
	DisplayCategories(foodPlannerData.getIngredientCategories());
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void IngredientCategoriesScrollPanel::EnterIngredientCategory(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string category = std::string((IngredientCategoryEntry->GetValue()).mb_str());
	if (inputValid(category)) {
		if ((category != "") && (!foodPlannerData.findIngredientStoreCategory(category))) {
			IngredientCategoryEntry->SetValue("");
			DisplayCategory(category);
			SaveCategories(saved_info_path);
		}
		else {
			wxMessageBox("Enter a non duplicate category.");
		}
	}
	else {
		wxMessageBox("Invalid character used.");
	}
}
void IngredientCategoriesScrollPanel::SaveCategories(std::string saved_info_path) {
	std::vector<std::string> categories;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		categories.push_back(displayInfoGroups[i].category);
	}
	foodPlannerData.setStoreCategories(categories);
	fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
}

// Public frame functions
void IngredientCategoriesDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	IngredientCategoriesPanel->cleanUp();
	EndModal(wxCANCEL);
}