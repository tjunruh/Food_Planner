#include "IngredientNames.h"

IngredientNamesDialog* IngredientNamesWin;
IngredientNamesScrollPanel* IngredientNamesPanel;

IngredientNamesScrollPanel::IngredientNamesScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;

	for (int i = 0; i < 3; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}

	mainSizer->Add(0, skipLine);

	Directions = new wxStaticText(this, wxID_ANY, wxT("Type name and press enter."));
	sizers[0]->Add(Directions);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	IngredientNameEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[1]->Add(IngredientNameEntry);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	ingredientHeader = new wxStaticText(this, wxID_ANY, wxT("Ingredient Names:"));
	sizers[2]->Add(ingredientHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(ingredientSizer);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	boost::function<void(wxCommandEvent&)> enterNameFunctor(boost::bind(&IngredientNamesScrollPanel::EnterName, this, _1, saved_info_path));
	IngredientNameEntry->Bind(wxEVT_TEXT_ENTER, enterNameFunctor, wxID_ANY);
}
IngredientNamesDialog::IngredientNamesDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &IngredientNamesDialog::CloseDialog, this, wxID_ANY);
}

// Private panel functions
void IngredientNamesScrollPanel::cleanUp() {
	IngredientNameEntry->SetValue("");
	ingredientSizer->Clear(TRUE);
	displayInfoGroups.clear();
}
void IngredientNamesScrollPanel::DisplayIngredientName(std::string name) {
	displayInfoGroup group;
	group.nameLabel = new wxStaticText(this, wxID_ANY, name);
	group.renameName = new wxButton(this, wxID_ANY, wxT("Rename"));
	group.newNameSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.name = name;

	group.newNameSizer->Add(group.nameLabel);
	group.newNameSizer->Add(group.renameName);
	group.spacer->Add(0, 2);

	formatSizer(group.newNameSizer, horizontalMargin, frameWidth);

	ingredientSizer->Add(group.newNameSizer);
	ingredientSizer->Add(group.spacer);

	mainSizer->Layout();

	group.renameName->Bind(wxEVT_BUTTON, &IngredientNamesScrollPanel::RenameName, this);
	displayInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void IngredientNamesScrollPanel::DisplayIngredientNames(std::vector<wxString> names) {
	names = labelOrganizer.alphabetizeVector(names);
	for (int i = 0; i < names.size(); i++) {
		DisplayIngredientName(std::string(names[i].mb_str()));
	}
}
void IngredientNamesScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void IngredientNamesScrollPanel::RenameName(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		if (displayInfoGroups[i].renameName->GetId() == button) {
			index = i;
			break;
		}
	}
	renameDataPanel->setUp(renameDataPanel->ingredientNames, displayInfoGroups[index].name);
	renameDataWin->ShowModal();
	cleanUp();
	DisplayIngredientNames(foodPlannerData.getIngredientNames());
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void IngredientNamesScrollPanel::EnterName(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string name = std::string((IngredientNameEntry->GetValue()).mb_str());
	if (inputValid(name)) {
		if ((name != "") && (!foodPlannerData.findIngredientName(name))) {
			IngredientNameEntry->SetValue("");
			DisplayIngredientName(name);
			SaveNames(saved_info_path);
		}
		else {
			wxMessageBox("Enter a non duplicate name.");
		}
	}
	else {
		wxMessageBox("Invalid character used.");
	}
}
void IngredientNamesScrollPanel::SaveNames(std::string saved_info_path) {
	std::vector<std::string> names;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		names.push_back(displayInfoGroups[i].name);
	}
	foodPlannerData.setIngredientNames(names);

	fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
}

// Public frame functions
void IngredientNamesDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	IngredientNamesPanel->cleanUp();
	EndModal(wxID_CANCEL);
}