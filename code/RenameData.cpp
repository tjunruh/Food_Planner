#include "RenameData.h"
renameDataDialog* renameDataWin;
renameDataScrollPanel* renameDataPanel;

renameDataScrollPanel::renameDataScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id) {
	frameWidth = size.x;
	for (int i = 0; i < 6; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	wxFont headerFont = wxFont(wxFontInfo(12).Bold().Underlined());

	oldNameLabel = new wxStaticText(this, wxID_ANY, wxT(""));
	oldNameLabel->SetFont(headerFont);
	sizers[5]->Add(oldNameLabel);
	formatSizer(sizers[5], horizontalMargin, frameWidth);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(sizers[5]);
	mainSizer->Add(0, skipLine);

	DirectionsHeader = new wxStaticText(this, wxID_ANY, wxT("Rename with a new or existing name"));
	DirectionsHeader->SetFont(headerFont);
	sizers[0]->Add(DirectionsHeader);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	wxString choices[2] = { "New","Existing" };
	oldOrNewName = new wxRadioBox(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, 2, choices);
	sizers[1]->Add(oldOrNewName);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, skipLine);

	newNameEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[3]->Add(newNameEntry);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, skipLine);

	oldNameEntry = new wxChoice(this, wxID_ANY, newNameEntry->GetPosition(), wxDefaultSize, 0, NULL);
	oldNameEntry->Show(FALSE);

	DependanciesHeader = new wxStaticText(this, wxID_ANY, wxT("Dependancies"));
	topLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	bottomLine = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	DependanciesHeader->SetFont(headerFont);
	sizers[2]->Add(DependanciesHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(topLine);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(displaySizer);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(bottomLine);
	mainSizer->Add(0, skipLine);

	Rename = new wxButton(this, wxID_ANY, wxT("Raname"));
	sizers[4]->Add(frameWidth - Rename->GetSize().x - horizontalMargin * 2, 0);
	sizers[4]->Add(Rename);
	formatSizer(sizers[4], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[4]);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	oldOrNewName->Bind(wxEVT_RADIOBOX, &renameDataScrollPanel::oldOrNewNamePressed, this, wxID_ANY);
	boost::function<void(wxCommandEvent&)> renameFunctor(boost::bind(&renameDataScrollPanel::RenamePressed, this, _1, saved_info_path));
	Rename->Bind(wxEVT_BUTTON, renameFunctor, wxID_ANY);
}

renameDataDialog::renameDataDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size) {
	Bind(wxEVT_CLOSE_WINDOW, &renameDataDialog::closeDialog, this, wxID_ANY);
}

void renameDataScrollPanel::cleanUp() {
	displaySizer->Clear(TRUE);
	displayGroups.clear();
	oldNameEntry->Clear();
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::displaySingleData(wxString text) {
	displayGroup group;
	group.label = new wxStaticText(this, wxID_ANY, text);
	group.newLabelSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);

	group.newLabelSizer->Add(horizontalMargin, 0);
	group.newLabelSizer->Add(group.label);
	group.spacer->Add(0, verticalMargin);

	displaySizer->Add(group.newLabelSizer);
	displaySizer->Add(group.spacer);

	mainSizer->Layout();

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::displayMultipleData(std::vector <std::string> text) {
	text = labelOrganizer.alphabetizeVector(text);
	for (int i = 0; i < text.size(); i++) {
		displaySingleData(text[i]);
	}
}
void renameDataScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth) {
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
int renameDataScrollPanel::getLongestTextSize(wxChoice* choice) {
	int longestText = 0;
	for (int i = 0; i < choice->GetCount(); i++) {
		if ((choice->GetTextExtent(choice->GetString(i)).x > longestText)) {
			longestText = choice->GetTextExtent(choice->GetString(i)).x;
		}
	}
	return longestText;
}
void renameDataScrollPanel::RenamePressed(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string oldName = std::string(oldNameLabel->GetLabelText().mb_str());
	if (oldOrNewName->GetSelection() == 1) {
		int oldNameIndex = oldNameEntry->GetSelection();
		if (oldNameIndex != wxNOT_FOUND) {
			std::string newName = std::string(oldNameEntry->GetString(oldNameIndex).mb_str());
			if (mode == ingredientStoreCategories) {
				foodPlannerData.renameIngredientStoreCategory(oldName, newName);
			}
			else if (mode == ingredientNames) {
				foodPlannerData.renameIngredient(oldName, newName);
			}
			else if (mode == units) {
				foodPlannerData.renameUnit(oldName, newName);
			}
			else if (mode == mealCategories) {
				foodPlannerData.renameMealCategory(oldName, newName);
			}
			else if (mode == ingredientPantryCategories) {
				foodPlannerData.renameIngredientPantryCategory(oldName, newName);
			}
			cleanUp();
			fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
			renameDataWin->EndModal(wxCANCEL);
		}
		else {
			wxMessageBox("Select a new name.");
		}
	}
	else if (oldOrNewName->GetSelection() == 0) {
		std::string newName = std::string(newNameEntry->GetValue().mb_str());
		if (newName != "") {
			if (mode == ingredientStoreCategories) {
				foodPlannerData.renameIngredientStoreCategory(oldName, newName);
			}
			else if (mode == ingredientNames) {
				foodPlannerData.renameIngredient(oldName, newName);
			}
			else if (mode == units) {
				foodPlannerData.renameUnit(oldName, newName);
			}
			else if (mode == mealCategories) {
				foodPlannerData.renameMealCategory(oldName, newName);
			}
			else if (mode == ingredientPantryCategories) {
				foodPlannerData.renameIngredientPantryCategory(oldName, newName);
			}
			cleanUp();
			fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
			renameDataWin->EndModal(wxCANCEL);
		}
		else {
			wxMessageBox("Type a new name.");
		}
	}
}
void renameDataScrollPanel::oldOrNewNamePressed(wxCommandEvent& WXUNUSED(event)) {
	if (oldOrNewName->GetSelection() == 1) {
		showOldNames();
	}
	else if (oldOrNewName->GetSelection() == 0) {
		showNewNames();
	}
}
void renameDataScrollPanel::setMode(int selectedMode) {
	mode = selectedMode;
}
void renameDataScrollPanel::setOldName(std::string name) {
	std::vector <std::string> dependants;
	oldNameLabel->SetLabelText(name);
	sizers[5]->Detach(oldNameLabel);
	sizers[5]->Clear(TRUE);
	sizers[5]->Add(oldNameLabel);
	formatSizer(sizers[5], horizontalMargin, frameWidth);

	if (mode == ingredientStoreCategories) {
		dependants = foodPlannerData.getIngredientNamesOfStoreCategory(name);
	}
	else if (mode == ingredientNames) {

	}
	else if (mode == units) {
		dependants = foodPlannerData.getIngredientNamesOfUnit(name);
	}
	else if (mode == mealCategories) {
		dependants = foodPlannerData.getMealNamesOfCategory(name);
	}
	else if (mode == ingredientPantryCategories) {
		dependants = foodPlannerData.getIngredientNamesOfPantryCategory(name);
	}
	displayMultipleData(dependants);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::setExistingNames() {
	if (mode == ingredientStoreCategories) {
		oldNameEntry->Append(foodPlannerData.getIngredientCategories());
	}
	else if (mode == ingredientNames) {
		oldNameEntry->Append(foodPlannerData.getIngredientNames());
	}
	else if (mode == units) {
		oldNameEntry->Append(foodPlannerData.getUnits());
	}
	else if (mode == mealCategories) {
		oldNameEntry->Append(foodPlannerData.getMealCategories());
	}
	else if (mode == ingredientPantryCategories) {
		oldNameEntry->Append(foodPlannerData.getPantryCategories());
	}
	oldNameEntry->SetSize(oldNameEntry->GetSizeFromTextSize(getLongestTextSize(oldNameEntry), -1));
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::setUp(int selectMode, std::string oldName) {
	setMode(selectMode);
	setExistingNames();
	setOldName(oldName);

}
void renameDataScrollPanel::updateOldNames(std::vector<wxString> labels) {
	oldNameEntry->Clear();
	oldNameEntry->Append(labels);
	if (oldNameEntry->GetCount() != 0) {
		oldNameEntry->SetSize(oldNameEntry->GetSizeFromTextSize(getLongestTextSize(oldNameEntry), -1));
		sizers[3]->Detach(oldNameEntry);
		sizers[3]->Detach(newNameEntry);
		sizers[3]->Clear(TRUE);
		if (oldNameEntry->IsShown()) {
			sizers[3]->Add(oldNameEntry);
			formatSizer(sizers[3], horizontalMargin, frameWidth);
		}
	}
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::showNewNames() {
	oldNameEntry->Show(FALSE);
	sizers[3]->Detach(oldNameEntry);
	sizers[3]->Clear(TRUE);
	sizers[3]->Add(newNameEntry);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	newNameEntry->Show(TRUE);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void renameDataScrollPanel::showOldNames() {
	newNameEntry->Show(FALSE);
	sizers[3]->Detach(newNameEntry);
	sizers[3]->Clear(TRUE);
	sizers[3]->Add(oldNameEntry);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	oldNameEntry->Show(TRUE);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}

void renameDataDialog::closeDialog(wxCloseEvent& WXUNUSED(event)) {
	renameDataPanel->cleanUp();
	EndModal(wxCANCEL);
}