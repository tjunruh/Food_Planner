#include "EditData.h"

editDataDialog* editDataWin;
editDataScrollPanel* editDataPanel;
editDataScrollPanel::editDataScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id)
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

	dataEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[1]->Add(dataEntry);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	dataHeader = new wxStaticText(this, wxID_ANY, wxT(""));
	sizers[2]->Add(dataHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(dataSizer);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	boost::function<void(wxCommandEvent&)> enterCategoryFunctor(boost::bind(&editDataScrollPanel::EnterData, this, _1, saved_info_path));
	dataEntry->Bind(wxEVT_TEXT_ENTER, enterCategoryFunctor, wxID_ANY);
}

editDataDialog::editDataDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &editDataDialog::CloseDialog, this, wxID_ANY);
}

// Private panel functions
void editDataScrollPanel::cleanUp() {
	dataEntry->SetValue("");
	dataSizer->Clear(TRUE);
	displayDataInfoGroups.clear();
}
void editDataScrollPanel::DisplayData(std::string data) {
	displayCategoryInfoGroup group;
	std::vector<std::string> categories;
	int index = 0;
	group.dataLabel = new wxStaticText(this, wxID_ANY, data);
	group.renameData = new wxButton(this, wxID_ANY, wxT("Rename"));
	group.newDataSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.data = data;

	group.newDataSizer->Add(group.dataLabel);
	group.newDataSizer->Add(group.renameData);
	group.spacer->Add(0, 2);

	formatSizer(group.newDataSizer, horizontalMargin, frameWidth);

	for (int i = 0; i < displayDataInfoGroups.size(); i++) {
		categories.push_back(displayDataInfoGroups[i].data);
	}
	categories = labelOrganizer.alphabetizeVector(categories);
	index = labelOrganizer.positionToInsert(categories, group.data);
	dataSizer->Insert(index * 2, group.newDataSizer);
	dataSizer->Insert((index * 2) + 1, group.spacer);

	mainSizer->Layout();

	group.renameData->Bind(wxEVT_BUTTON, &editDataScrollPanel::RenameData, this);
	displayDataInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void editDataScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void editDataScrollPanel::RenameData(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayDataInfoGroups.size(); i++) {
		if (displayDataInfoGroups[i].renameData->GetId() == button) {
			index = i;
			break;
		}
	}
	displayDataInfoGroups[index].newDataSizer->Clear(TRUE);
	displayDataInfoGroups[index].spacer->Clear(TRUE);
	mainSizer->Layout();
	displayDataInfoGroups.erase(displayDataInfoGroups.begin() + index);
}
void editDataScrollPanel::EnterData(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string data = std::string((dataEntry->GetValue()).mb_str());
	if (data != "") {
		if (inputValid(data)) {
			if (mode == ingredientStoreCategories) {
				if (!foodPlannerData.findIngredientStoreCategory(data)) {
					dataEntry->SetValue("");
					DisplayData(data);
					std::vector<std::string> data;
					for (int i = 0; i < displayDataInfoGroups.size(); i++) {
						data.push_back(displayDataInfoGroups[i].data);
					}
					foodPlannerData.setStoreCategories(data);
				}
				else {
					wxMessageBox("Enter a non-duplicate.");
				}
			}
			else if (mode == ingredientNames) {

			}
			else if (mode == units) {

			}
			else if (mode == mealCategories) {

			}
			else if (mode == ingredientPantryCategories) {

			}
			if ((data != "") && (!foodPlannerData.findMealCategory(category))) {
				MealCategoryEntry->SetValue("");
				DisplayAndSaveOverallMealCategory(category);
				SaveCategories(saved_info_path);
			}
			else {
				wxMessageBox("Enter a non duplicate.");
			}
		}
		else {
			wxMessageBox("Invalid character used.");
		}
	}
	else {
		wxMessageBox("Entry is blank.");
	}

}
void editDataScrollPanel::SaveData(std::string saved_info_path) {
	std::vector<std::string> data;
	for (int i = 0; i < displayDataInfoGroups.size(); i++) {
		data.push_back(displayDataInfoGroups[i].data);
	}
	foodPlannerData.setMealCategories(categories);
	fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
	categories.clear();

}
void editDataScrollPanel::setMode(int selectedMode) {
	mode = selectedMode;
	if (mode == ingredientStoreCategories) {
		dataHeader->SetLabelText("Categories:");
	}
	else if (mode == ingredientNames) {
		dataHeader->SetLabelText("Names:");
	}
	else if (mode == units) {
		dataHeader->SetLabelText("Units:");
	}
	else if (mode == mealCategories) {
		dataHeader->SetLabelText("Categories:");
	}
	else if (mode == ingredientPantryCategories) {
		dataHeader->SetLabelText("Categories:");
	}
	sizers[2]->Detach(dataHeader);
	sizers[2]->Clear(TRUE);
	sizers[2]->Add(dataHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}

// Public frame functions
void editDataDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	EndModal(wxCANCEL);
	MealCategoriesPanel->cleanUp();
}