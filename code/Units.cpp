#include "Units.h"

UnitsDialog* UnitsWin;
UnitsScrollPanel* UnitsPanel;

UnitsScrollPanel::UnitsScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string saved_info_path) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	for (int i = 0; i < 3; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}

	mainSizer->Add(0, skipLine);

	Directions = new wxStaticText(this, wxID_ANY, wxT("Type unit and press enter."));
	sizers[0]->Add(Directions);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	UnitEntry = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
	sizers[1]->Add(UnitEntry);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	UnitsHeader = new wxStaticText(this, wxID_ANY, wxT("Units:"));
	sizers[2]->Add(UnitsHeader);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(unitSizer);
	mainSizer->Add(0, skipLine);


	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	boost::function<void(wxCommandEvent&)> enterUnitFunctor(boost::bind(&UnitsScrollPanel::EnterUnit, this, _1, saved_info_path));
	UnitEntry->Bind(wxEVT_TEXT_ENTER, enterUnitFunctor, wxID_ANY);
}

UnitsDialog::UnitsDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size)
{
	Bind(wxEVT_CLOSE_WINDOW, &UnitsDialog::CloseDialog, this, wxID_ANY);
}

// Private panel functions
void UnitsScrollPanel::cleanUp() {
	UnitEntry->SetValue("");
	unitSizer->Clear(TRUE);
	displayInfoGroups.clear();
}
void UnitsScrollPanel::DisplayUnit(std::string unit) {
	displayCategoryInfoGroup group;
	group.unitLabel = new wxStaticText(this, wxID_ANY, unit);
	group.renameUnit = new wxButton(this, wxID_ANY, wxT("Rename"));
	group.newUnitSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.unit = unit;

	group.newUnitSizer->Add(group.unitLabel);
	group.newUnitSizer->Add(group.renameUnit);
	group.spacer->Add(0, 2);

	formatSizer(group.newUnitSizer, horizontalMargin, frameWidth);
	unitSizer->Add(group.newUnitSizer);
	unitSizer->Add(group.spacer);

	mainSizer->Layout();

	group.renameUnit->Bind(wxEVT_BUTTON, &UnitsScrollPanel::RenameUnit, this);

	displayInfoGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void UnitsScrollPanel::DisplayUnits(std::vector<wxString> units) {
	units = labelOrganizer.alphabetizeVector(units);
	for (int i = 0; i < units.size(); i++) {
		DisplayUnit(std::string(units[i].mb_str()));
	}
}
void UnitsScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void UnitsScrollPanel::EnterUnit(wxCommandEvent& WXUNUSED(event), std::string saved_info_path) {
	std::string unit = std::string((UnitEntry->GetValue()).mb_str());
	if (inputValid(unit)) {
		if ((unit != "") && (!foodPlannerData.findUnit(unit))) {
			UnitEntry->SetValue("");
			DisplayUnit(unit);
			SaveUnit(saved_info_path);
		}
		else {
			wxMessageBox("Enter a non duplicate category.");
		}
	}
}
void UnitsScrollPanel::RenameUnit(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		if (displayInfoGroups[i].renameUnit->GetId() == button) {
			index = i;
			break;
		}
	}
	renameDataPanel->setUp(renameDataPanel->units, displayInfoGroups[index].unit);
	renameDataWin->ShowModal();
	cleanUp();
	DisplayUnits(foodPlannerData.getUnits());
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void UnitsScrollPanel::SaveUnit(std::string saved_info_path) {
	std::vector<std::string> units;
	for (int i = 0; i < displayInfoGroups.size(); i++) {
		units.push_back(displayInfoGroups[i].unit);
	}
	foodPlannerData.setUnits(units);
	fileReaderWriter.write_file(saved_info_path, fileReaderWriter.Stringify(foodPlannerData));
}

// Public frame functions
void UnitsDialog::CloseDialog(wxCloseEvent& WXUNUSED(event)) {
	UnitsPanel->cleanUp();
	EndModal(wxCANCEL);
}