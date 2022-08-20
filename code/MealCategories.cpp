#include "MealCategories.h"

MealCategoriesDialog* MealCategoriesWin;
MealCategoriesScrollPanel* MealCategoriesPanel;
MealCategoriesScrollPanel::MealCategoriesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id)
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

	MealCategoryEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[1]->Add(MealCategoryEntry);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	categoriesHeader = new wxStaticText(this, wxID_ANY, wxT("Categories:"));
	sizers[2]->Add(categoriesHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(categorySizer);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	boost::function<void(wxCommandEvent&)> enterCategoryFunctor(boost::bind(&MealCategoriesScrollPanel::EnterCategory, this, _1, saved_info_path));
	MealCategoryEntry->Bind(wxEVT_TEXT_ENTER, enterCategoryFunctor, wxID_ANY);
}

MealCategoriesDialog::MealCategoriesDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &MealCategoriesDialog::CloseDialog, this, wxID_ANY);
}

// Private panel functions
void MealCategoriesScrollPanel::cleanUp() {
	MealCategoryEntry->SetValue("");
	categorySizer->Clear(TRUE);
	displayCategoryInfoGroups.clear();
}
void MealCategoriesScrollPanel::DisplayCategory(std::string category) {
	displayCategoryInfoGroup group;
	group.categoryLabel = new wxStaticText(this, wxID_ANY, category);
	group.renameCategory = new wxButton(this, wxID_ANY, wxT("Rename"));
	group.newCategorySizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.category = category;

	group.newCategorySizer->Add(group.categoryLabel);
	group.newCategorySizer->Add(group.renameCategory);
	group.spacer->Add(0, 2);

	formatSizer(group.newCategorySizer, horizontalMargin, frameWidth);

	categorySizer->Add(group.newCategorySizer);
	categorySizer->Add(group.spacer);

	mainSizer->Layout();

	group.renameCategory->Bind(wxEVT_BUTTON, &MealCategoriesScrollPanel::RenameCategory, this);
	displayCategoryInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealCategoriesScrollPanel::DisplayCategories(std::vector<wxString> categories) {
	categories = labelOrganizer.alphabetizeVector(categories);
	for (int i = 0; i < categories.size(); i++) {
		DisplayCategory(std::string(categories[i].mb_str()));
	}
}
void MealCategoriesScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void MealCategoriesScrollPanel::RenameCategory(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		if (displayCategoryInfoGroups[i].renameCategory->GetId() == button) {
			index = i;
			break;
		}
	}
	renameDataPanel->setUp(renameDataPanel->mealCategories, displayCategoryInfoGroups[index].category);
	renameDataWin->ShowModal();
	cleanUp();
	DisplayCategories(foodPlannerData.getMealCategories());
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MealCategoriesScrollPanel::EnterCategory(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string category = std::string((MealCategoryEntry->GetValue()).mb_str());
	if (inputValid(category)) {
		if ((category != "") && (!foodPlannerData.findMealCategory(category))) {
			MealCategoryEntry->SetValue("");
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
void MealCategoriesScrollPanel::SaveCategories(std::string saved_info_path) {
	std::vector<std::string> categories;
	for (int i = 0; i < displayCategoryInfoGroups.size(); i++) {
		categories.push_back(displayCategoryInfoGroups[i].category);
	}
	foodPlannerData.setMealCategories(categories);
	fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
	categories.clear();
	
}

// Public frame functions
void MealCategoriesDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	EndModal(wxCANCEL);
	MealCategoriesPanel->cleanUp();
}