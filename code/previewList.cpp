#include "previewList.h"

previewListScrollPanel* previewListPanel;
previewListDialog* previewListWin;

previewListScrollPanel::previewListScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size, std::string programPath, monthDayYear beginDate, monthDayYear endDate) : wxScrolledWindow(parent, id) {

	frameWidth = size.x;
	for (int i = 0; i < 4; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	wxFont headerFont = wxFont(wxFontInfo(12).Bold().Underlined());
	listHeader = new wxStaticText(this, wxID_ANY, wxT("Edit Grocery List"));
	listHeader->SetFont(headerFont);
	sizers[0]->Add(listHeader);
	formatSizer(sizers[0], horizontalMargin, frameWidth);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, skipLine);

	aboveIngredients = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	mainSizer->Add(aboveIngredients);
	mainSizer->Add(0, skipLine);

	mainSizer->Add(ingredientSizer);
	mainSizer->Add(0, skipLine);

	belowIngredients = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	mainSizer->Add(belowIngredients);
	mainSizer->Add(0, skipLine);

	storesHeader = new wxStaticText(this, wxID_ANY, wxT("Select Store:"));
	storesHeader->SetFont(headerFont);
	sizers[1]->Add(storesHeader);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, skipLine);

	std::vector<wxString> choices = foodPlannerData.getListStoreNames();
	stores = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices.size(), choices.data());
	sizers[2]->Add(stores);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, skipLine);

	print = new wxButton(this, wxID_ANY, wxT("Print"));
	//save = new wxButton(this, wxID_ANY, wxT("Save"));
	sizers[3]->Add(frameWidth - print->GetSize().x - horizontalMargin * 2, 0);
	//sizers[3]->Add(save);
	sizers[3]->Add(print);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	print->Bind(wxEVT_BUTTON, &previewListScrollPanel::PrintPressed, this, wxID_ANY);
	boost::function<void(wxCommandEvent&)> saveFunctor(boost::bind(&previewListScrollPanel::SavePressed, this, _1, programPath, beginDate, endDate));
	//save->Bind(wxEVT_BUTTON, saveFunctor, wxID_ANY);
}

previewListDialog::previewListDialog(const wxString& title, const wxPoint& pos, const wxSize& size) : wxDialog((wxDialog*)NULL, -1, title, pos, size) {
	Bind(wxEVT_CLOSE_WINDOW, &previewListDialog::closeDialog, this, wxID_ANY);
	Bind(wxEVT_SHOW, &previewListDialog::update, this, wxID_ANY);
}

void previewListScrollPanel::cleanUp() {
	stores->SetSelection(wxNOT_FOUND);
	stores->Clear();
	ingredientSizer->Clear(TRUE);
	displayIngredientGroups.clear();
}
void previewListScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const float frameWidth) {
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
int previewListScrollPanel::getLongestTextSize(wxChoice* choice) {
	int longestText = 0;
	for (int i = 0; i < choice->GetCount(); i++) {
		if ((choice->GetTextExtent(choice->GetString(i)).x > longestText)) {
			longestText = choice->GetTextExtent(choice->GetString(i)).x;
		}
	}
	return longestText;
}
void previewListScrollPanel::DisplayIngredient(Ingredient item) {
	displayIngredientGroup group;
	group.deleteIngredient = new wxButton(this, wxID_ANY, wxT("x"));
	group.ingredientName = new wxStaticText(this, wxID_ANY, item.Name);
	group.unit = new wxStaticText(this, wxID_ANY, item.Unit);
	group.amount = new wxTextCtrl(this, wxID_ANY, round(item.Amount, 3));
	group.category = item.storeCategory;
	
	group.newIngredientSizer = new wxBoxSizer(wxHORIZONTAL);
	group.newIngredientSizer->Add(50, 0);
	group.newIngredientSizer->Add(group.ingredientName);
	group.newIngredientSizer->Add(5, 0);
	group.newIngredientSizer->Add(group.amount);
	group.newIngredientSizer->Add(5, 0);
	group.newIngredientSizer->Add(group.unit);
	group.newIngredientSizer->Add(frameWidth - group.ingredientName->GetSize().x - group.amount->GetSize().x - group.unit->GetSize().x - group.deleteIngredient->GetSize().x - 15 - horizontalMargin * 2, 0);
	group.newIngredientSizer->Add(group.deleteIngredient);

	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer->Add(0, 2);

	ingredientSizer->Add(group.newIngredientSizer);
	ingredientSizer->Add(group.spacer);

	mainSizer->Layout();

	group.deleteIngredient->Bind(wxEVT_BUTTON, &previewListScrollPanel::DeleteIngredient, this, wxID_ANY);
	displayIngredientGroups.push_back(group);

	this->FitInside();
	this->SetScrollRate(5, 5);

}
void previewListScrollPanel::DisplayPantryCategory(wxString category) {
	wxBoxSizer* newSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label = new wxStaticText(this, wxID_ANY, category);
	newSizer->Add(label);
	formatSizer(newSizer, horizontalMargin, frameWidth);
	ingredientSizer->Add(newSizer);
	mainSizer->Layout();

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void previewListScrollPanel::DeleteIngredient(wxCommandEvent& event) {
	int button = event.GetId();
	int index = 0;
	for (int i = 0; i < displayIngredientGroups.size(); i++) {
		if (displayIngredientGroups[i].deleteIngredient->GetId() == button) {
			index = i;
			break;
		}
	}
	displayIngredientGroups[index].newIngredientSizer->Clear(TRUE);
	displayIngredientGroups[index].spacer->Clear(TRUE);
	mainSizer->Layout();
	displayIngredientGroups.erase(displayIngredientGroups.begin() + index);

	this->FitInside();
	this->SetScrollRate(5, 5);
}
void previewListScrollPanel::PrintPressed(wxCommandEvent& WXUNUSED(event)) {
	std::vector<Ingredient> ingredients;
	std::string printableIngredientList;
	buildList listHandler;
	int storesIndex = stores->GetSelection();
	if (storesIndex != wxNOT_FOUND) {
		List listTemplate = foodPlannerData.getList(std::string(stores->GetString(storesIndex).mb_str()));
		for (int i = 0; i < displayIngredientGroups.size(); i++) {
			Ingredient item;
			item.Name = displayIngredientGroups[i].ingredientName->GetLabelText();
			item.storeCategory = displayIngredientGroups[i].category;
			item.Unit = displayIngredientGroups[i].unit->GetLabelText();
			(displayIngredientGroups[i].amount->GetValue().ToDouble(&item.Amount));
			ingredients.push_back(item);
		}
		printableIngredientList = listHandler.generateStringToPrint(ingredients, listTemplate);
		QuickPrint* myprint;
		myprint = new QuickPrint(1, wxT("Grocery List"));
		myprint->setPrintText(printableIngredientList);
		myprint->preparePrint(true);

		wxPrintDialogData data(myprint->getPrintData());
		wxPrinter printer(&data);
		const bool success = printer.Print(NULL, myprint, true);
	}
	else {
		wxMessageBox("Enter a store.");
	}
	
}
std::string previewListScrollPanel::round(double num, int decimalPlaces) {
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
void previewListScrollPanel::SavePressed(wxCommandEvent& event, std::string programPath, monthDayYear beginDate, monthDayYear endDate) {
	std::vector<Ingredient> ingredients;
	std::string ingredientList;
	buildList listHandler;
	int storesIndex = stores->GetSelection();
	if (storesIndex != wxNOT_FOUND) {
		List listTemplate = foodPlannerData.getList(std::string(stores->GetString(storesIndex).mb_str()));
		for (int i = 0; i < displayIngredientGroups.size(); i++) {
			Ingredient item;
			item.Name = displayIngredientGroups[i].ingredientName->GetLabelText();
			item.storeCategory = displayIngredientGroups[i].category;
			item.Unit = displayIngredientGroups[i].unit->GetLabelText();
			(displayIngredientGroups[i].amount->GetValue().ToDouble(&item.Amount));
			ingredients.push_back(item);
		}
		ingredientList = listHandler.generateStringToPrint(ingredients, listTemplate);
		std::string filePath = programPath + "/" + std::to_string(beginDate.month) + "-" + std::to_string(beginDate.day) + "-" + std::to_string(beginDate.year) + " to " + std::to_string(endDate.month) + "-" + std::to_string(endDate.day) + "-" + std::to_string(endDate.year);
		fileReaderWriter.write_file(filePath, ingredientList);
	}
	else {
		wxMessageBox("Enter a store.");
	}
}
void previewListScrollPanel::updateStores() {
	stores->Clear();
	stores->Append(foodPlannerData.getListStoreNames());
	if (stores->GetCount() != 0) {
		stores->SetSize(stores->GetSizeFromTextSize(getLongestTextSize(stores), -1));
		sizers[2]->Detach(stores);
		sizers[2]->Clear(TRUE);
		sizers[2]->Add(stores);
		formatSizer(sizers[2], horizontalMargin, frameWidth);
		mainSizer->Layout();
	}
}

void previewListDialog::closeDialog(wxCloseEvent& WXUNUSED(event)) {
	previewListPanel->cleanUp();
	EndModal(wxCANCEL);
}
void previewListDialog::update(wxShowEvent& WXUNUSED(event)) {
	if (this->IsShown()) {
		previewListPanel->updateStores();
	}
}