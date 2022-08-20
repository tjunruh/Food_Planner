#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "Food_Planner.h"

MainFrame* MainWin;
MainScrollPanel* MainPanel;

IMPLEMENT_APP(MainApp)

//SavedInfo foodPlannerData;
calender dateHandler;
monthDayYear date;
monthDayYear rangeDate;
std::string saved_info_path;
std::string test_path;
bool MainApp::OnInit()
{
	wxFileName exPath(wxStandardPaths::Get().GetExecutablePath());
	wxString path(exPath.GetPath());
	std::string address = std::string(path.mb_str());

	saved_info_path = address + "\\saved_info.txt";
	test_path = address + "\\test_file.txt";

	foodPlannerData = fileReaderWriter.Parse(fileReaderWriter.read_file(test_path));

	time_t ttime = time(0);
	tm* current_time = localtime(&ttime);
	date.year = 1900 + current_time->tm_year;
	date.month = 1 + current_time->tm_mon;
	date.day = current_time->tm_mday;
	rangeDate = date;

	MainWin = new MainFrame(wxT("Mom's Cooking Planner"), wxDefaultPosition, wxSize(600, 600));
	MealWin = new MealDialog(wxT("Recipies"), wxDefaultPosition, wxSize(1800, 600));
	ListWin = new ListDialog(wxT("Organize Existing List"), wxDefaultPosition, wxSize(600, 600));
	previewListWin = new previewListDialog(wxT("List Previewer"), wxDefaultPosition, wxSize(600, 600));
	renameDataWin = new renameDataDialog(wxT("Rename"), wxDefaultPosition, wxSize(600, 600));

	MainPanel = new MainScrollPanel(MainWin, wxID_ANY, wxSize(600, 600));
	MealPanel = new MealScrollPanel(MealWin, wxID_ANY, wxSize(1600, 600), MainPanel, test_path);
	ListPanel = new ListScrollPanel(ListWin, wxID_ANY, wxSize(600, 600), test_path);
	previewListPanel = new previewListScrollPanel(previewListWin, wxID_ANY, wxSize(600, 600), address, MainPanel->beginDate, MainPanel->endDate);;
	renameDataPanel = new renameDataScrollPanel(renameDataWin, wxID_ANY, renameDataWin->GetSize(), test_path);
	
	MainPanel->beginDate = date;
	MainPanel->endDate = date;
	MainPanel->updateMealOfTheDay();
	if (foodPlannerData.getChosenMeal(date).mealName != "") {
		MainPanel->displayChosenMeal(foodPlannerData.getChosenMeal(date));
	}
	else {
		ChosenMeal chosenMealOnStartUpDay;
		chosenMealOnStartUpDay.mealName = "Meal Not Chosen";
		chosenMealOnStartUpDay.date.day = date.day;
		chosenMealOnStartUpDay.date.month = date.month;
		chosenMealOnStartUpDay.date.year = date.year;
		MainPanel->displayChosenMeal(chosenMealOnStartUpDay);
	}
	
	MealWin->Show(FALSE);
	ListWin->Show(FALSE);
	previewListWin->Show(FALSE);
	
	MainWin->Show(TRUE);
	SetTopWindow(MainWin);


	return TRUE;
}

MainScrollPanel::MainScrollPanel(wxWindow* parent, wxWindowID id, const wxSize& size) : wxScrolledWindow(parent, id)
{
	frameWidth = size.x;
	wxFont headerFont = wxFont(wxFontInfo(12).Bold().Underlined());
	wxFont dateFont = wxFont(wxFontInfo(12).Bold());
	for (int i = 0; i < 12; i++) {
		sizers[i] = new wxBoxSizer(wxHORIZONTAL);
	}
	wxString dateLabel = std::to_string(date.month) + "/" + std::to_string(date.day) + "/" + std::to_string(date.year);
	Date = new wxStaticText(this, STATIC_TEXT_Date, dateLabel);
	Date->SetFont(dateFont);
	LeftDateArrow = new wxButton(this, BUTTON_LeftArrow, _T("<"));
	RightDateArrow = new wxButton(this, BUTTON_RightArrow, _T(">"));
	sizers[0]->Add(LeftDateArrow);
	sizers[0]->Add(Date);
	sizers[0]->Add(RightDateArrow);
	formatSizer(sizers[0], 75, frameWidth);
	mainSizer->Add(sizers[0]);
	mainSizer->Add(0, verticalMargin);

	wxString choices[2] = { "Category", "Specific" };
	MealType = new wxRadioBox(this, RADIO_BOX_MealType, _T("Pick Meal Selection Method"), wxDefaultPosition, wxDefaultSize, 2, choices);
	sizers[1]->Add(MealType);
	formatSizer(sizers[1], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[1]);
	mainSizer->Add(0, verticalMargin);

	MealOrCategory = new wxStaticText(this, STATIC_TEXT_MealOrCategory, _T("Pick Meal"));
	MealOrCategory->SetFont(headerFont);
	sizers[2]->Add(MealOrCategory);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[2]);
	mainSizer->Add(0, verticalMargin);

	std::vector<wxString> choices2 = labelOrganizer.alphabetizeVector(foodPlannerData.getMealCategories());
	EnterMealOrEnterCategory = new wxChoice(this, CHOICE_EnterMealOrEnterCategory, wxDefaultPosition, wxDefaultSize, choices2.size(), choices2.data());
	sizers[3]->Add(EnterMealOrEnterCategory);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[3]);
	mainSizer->Add(0, verticalMargin);

	PickMealOrGenerateMeal = new wxButton(this, wxID_ANY, wxT("Generate Meal"));
	sizers[4]->Add(PickMealOrGenerateMeal);
	formatSizer(sizers[4], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[4]);
	mainSizer->Add(0, verticalMargin);

	topOfMeal = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	SelectedOrGeneratedMeal = new wxStaticText(this, STATIC_TEXT_SelectedOrGeneratedMeal, wxT("Selected Meal:"));
	SelectedOrGeneratedMeal->SetFont(headerFont);
	sizers[5]->Add(SelectedOrGeneratedMeal);
	formatSizer(sizers[5], horizontalMargin, frameWidth);
	mainSizer->Add(topOfMeal);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(sizers[5]);
	mainSizer->Add(0, skipLine);

	MealOfTheDay = new wxStaticText(this, wxID_ANY, wxT(""));
	bottomOfMeal = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(frameWidth, 2), wxLI_HORIZONTAL);
	sizers[10]->Add(MealOfTheDay);
	formatSizer(sizers[10], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[10]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(bottomOfMeal);
	mainSizer->Add(0, skipLine);

	DateRangeHeader = new wxStaticText(this, wxID_ANY, wxT("Number Days to Display Meal Plan:"));
	DateRangeHeader->SetFont(headerFont);
	sizers[6]->Add(DateRangeHeader);
	formatSizer(sizers[6], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[6]);
	mainSizer->Add(0, skipLine);

	Range = new wxStaticText(this, wxID_ANY, wxT("1"));
	LeftRangeArrow = new wxButton(this, wxID_ANY, wxT("<"));
	RightRangeArrow = new wxButton(this, wxID_ANY, wxT(">"));
	sizers[7]->Add(LeftRangeArrow);
	sizers[7]->Add(Range);
	sizers[7]->Add(RightRangeArrow);
	formatSizer(sizers[7], 75, frameWidth);
	mainSizer->Add(sizers[7]);
	mainSizer->Add(0, skipLine);

	EnterRange = new wxButton(this, wxID_ANY, wxT("Display Days"));
	sizers[8]->Add(EnterRange);
	formatSizer(sizers[8], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[8]);
	mainSizer->Add(0, skipLine);

	chosenMealsHeader = new wxStaticText(this, wxID_ANY, wxT("Chosen Meals:"));
	chosenMealsHeader->SetFont(headerFont);
	sizers[9]->Add(chosenMealsHeader);
	formatSizer(sizers[9], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[9]);
	mainSizer->Add(0, skipLine);
	mainSizer->Add(chosenMealSizer);
	mainSizer->Add(0, skipLine);

	BuildList = new wxButton(this, wxID_ANY, wxT("Build List"));
	sizers[11]->Add(BuildList);
	formatSizer(sizers[11], horizontalMargin, frameWidth);
	mainSizer->Add(sizers[11]);
	mainSizer->Add(0, skipLine);

	SetSizer(mainSizer);

	this->FitInside();
	this->SetScrollRate(5, 5);

	LeftDateArrow->Bind(wxEVT_BUTTON, &MainScrollPanel::LeftDateArrowPressed, this, wxID_ANY);
	RightDateArrow->Bind(wxEVT_BUTTON, &MainScrollPanel::RightDateArrowPressed, this, wxID_ANY);
	LeftRangeArrow->Bind(wxEVT_BUTTON, &MainScrollPanel::LeftRangeArrowPressed, this, wxID_ANY);
	RightRangeArrow->Bind(wxEVT_BUTTON, &MainScrollPanel::RightRangeArrowPressed, this, wxID_ANY);
	MealType->Bind(wxEVT_RADIOBOX, &MainScrollPanel::MealTypeSpecificOrCategory, this, wxID_ANY);
	EnterRange->Bind(wxEVT_BUTTON, &MainScrollPanel::EnterRangePressed, this, wxID_ANY);
	PickMealOrGenerateMeal->Bind(wxEVT_BUTTON, &MainScrollPanel::PickMealOrGenerateMealPressed, this, wxID_ANY);
	BuildList->Bind(wxEVT_BUTTON, &MainScrollPanel::buildListPressed, this, wxID_ANY);
	EnterMealOrEnterCategory->Bind(wxEVT_CHOICE, &MainScrollPanel::CategoryPicked, this, wxID_ANY);
}
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame((wxFrame*)NULL, -1, title, pos, size)
{
	CreateStatusBar(2);
	MainMenu = new wxMenuBar();
	EditMenu = new wxMenu();
	
	EditMenu->Append(MENU_Meal, wxT("&Meal"));
	EditMenu->Append(MENU_List, wxT("&List"));

	MainMenu->Append(EditMenu, wxT("Edit"));
	SetMenuBar(MainMenu);

	EditMenu->Bind(wxEVT_MENU, &MainFrame::OnMeal, this, MENU_Meal);
	EditMenu->Bind(wxEVT_MENU, &MainFrame::OnList, this, MENU_List);

	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::CloseFrame, this, wxID_ANY);
}

void MainScrollPanel::formatSizer(wxBoxSizer* sizer, const int margin, const int frameWidth) {
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
void MainScrollPanel::displayChosenMeal(ChosenMeal item) {
	displayChosenMealInfoGroup group;
	std::string labelDate = std::to_string(item.date.month) + "/" + std::to_string(item.date.day) + "/" + std::to_string(item.date.year);
	group.chosenMealLabel = new wxStaticText(this, wxID_ANY, (labelDate + "    " + item.mealName));
	group.newChosenMealSizer = new wxBoxSizer(wxHORIZONTAL);
	group.spacer = new wxBoxSizer(wxHORIZONTAL);
	group.chosenMealName = item.mealName;

	group.newChosenMealSizer->Add(group.chosenMealLabel);
	group.spacer->Add(0, 2);

	formatSizer(group.newChosenMealSizer, 100, frameWidth);

	chosenMealSizer->Add(group.newChosenMealSizer);
	chosenMealSizer->Add(group.spacer);

	mainSizer->Layout();

	displayChosenMealInfoGroups.push_back(group);
	this->FitInside();
	this->SetScrollRate(5, 5);
}
int MainScrollPanel::getLongestTextSize(wxChoice* choice) {
	int longestText = 0;
	for (int i = 0; i < choice->GetCount(); i++) {
		if ((choice->GetTextExtent(choice->GetString(i)).x > longestText)) {
			longestText = choice->GetTextExtent(choice->GetString(i)).x;
		}
	}
	return longestText;
}
void MainScrollPanel::updateMealsOrCategories() {
	EnterMealOrEnterCategory->Clear();
	if (PickMealOrGenerateMeal->GetLabelText() == "Enter Meal") {
		EnterMealOrEnterCategory->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getMealNames()));
	}
	else if (PickMealOrGenerateMeal->GetLabelText() == "Generate Meal") {
		EnterMealOrEnterCategory->Append(labelOrganizer.alphabetizeVector(foodPlannerData.getMealCategories()));
	}
	EnterMealOrEnterCategory->SetSize(EnterMealOrEnterCategory->GetSizeFromTextSize(getLongestTextSize(EnterMealOrEnterCategory), -1));
	sizers[3]->Detach(EnterMealOrEnterCategory);
	sizers[3]->Clear(TRUE);
	sizers[3]->Add(EnterMealOrEnterCategory);
	formatSizer(sizers[3], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainScrollPanel::updateDisplayedChosenMeals() {
	calender dateHandler;
	ChosenMeal mealAtDate;
	monthDayYear rangeDateTemp = rangeDate;
	chosenMealSizer->Clear(TRUE);
	displayChosenMealInfoGroups.clear();
	for (int i = 0; i < wxAtoi(Range->GetLabelText()); i++) {
		mealAtDate = foodPlannerData.getChosenMeal(rangeDateTemp);
		if (mealAtDate.mealName != "") {
			displayChosenMeal(mealAtDate);
		}
		else {
			mealAtDate.mealName = "Meal Not Chosen";
			mealAtDate.date = rangeDateTemp;
			displayChosenMeal(mealAtDate);
		}
		rangeDateTemp = dateHandler.getNewDate(rangeDateTemp, "increase");
	}
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainScrollPanel::updateMealOfTheDay() {
	ChosenMeal mealOfTheDay = foodPlannerData.getChosenMeal(date);
	if (mealOfTheDay.mealName == "") {
		MealOfTheDay->SetLabelText("None");
	}
	else {
		MealOfTheDay->SetLabelText(mealOfTheDay.mealName);
	}
	sizers[10]->Detach(MealOfTheDay);
	sizers[10]->Clear(TRUE);
	sizers[10]->Add(MealOfTheDay);
	formatSizer(sizers[10], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainScrollPanel::updateMealOfTheDayLabel() {
	sizers[5]->Detach(SelectedOrGeneratedMeal);
	sizers[5]->Clear(TRUE);
	sizers[5]->Add(SelectedOrGeneratedMeal);
	formatSizer(sizers[5], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainScrollPanel::updatePickMealOrGenerateMeal() {
	PickMealOrGenerateMeal->SetSize(PickMealOrGenerateMeal->GetSizeFromTextSize(PickMealOrGenerateMeal->GetTextExtent(PickMealOrGenerateMeal->GetLabelText()).x, -1));
	sizers[4]->Detach(PickMealOrGenerateMeal);
	sizers[4]->Clear(TRUE);
	sizers[4]->Add(PickMealOrGenerateMeal);
	formatSizer(sizers[4], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainScrollPanel::updateMealOrCategory() {
	sizers[2]->Detach(MealOrCategory);
	sizers[2]->Clear(TRUE);
	sizers[2]->Add(MealOrCategory);
	formatSizer(sizers[2], horizontalMargin, frameWidth);
	mainSizer->Layout();
	this->FitInside();
	this->SetScrollRate(5, 5);
}
void MainFrame::OnList(wxCommandEvent& WXUNUSED(event)) {
	ListWin->ShowModal();
	MainPanel->updateMealOrCategory();
}
void MainFrame::OnMeal(wxCommandEvent& WXUNUSED(event)) {
	MealWin->ShowModal();
	MainPanel->updatePickMealOrGenerateMeal();
}
void MainScrollPanel::buildListPressed(wxCommandEvent& WXUNUSED(event)) {
	std::vector<ChosenMeal> chosenMeals;
	std::vector<Ingredient> ingredients;
	buildList listHandler;
	for (int i = 0; i < displayChosenMealInfoGroups.size(); i++) {
		if (displayChosenMealInfoGroups[i].chosenMealName != "Meal Not Chosen") {
			chosenMeals.push_back(foodPlannerData.getChosenMeal(displayChosenMealInfoGroups[i].chosenMealName));
		}
	}
	ingredients = listHandler.assembleIngredients(chosenMeals);
	std::vector<wxString> pantryCategories = foodPlannerData.getPantryCategories();
	std::vector<Ingredient> ingredientsOfCategory;
	for (int j = 0; j < pantryCategories.size(); j++) {
		previewListPanel->DisplayPantryCategory(pantryCategories[j]);
		for (int i = 0; i < ingredients.size(); i++) {
			if (ingredients[i].pantryCategory == pantryCategories[j]) {
				ingredientsOfCategory.push_back(ingredients[i]);
			}
		}
		ingredientsOfCategory = labelOrganizer.alphabetizeVector(ingredientsOfCategory);
		for (int i = 0; i < ingredientsOfCategory.size(); i++) {
			previewListPanel->DisplayIngredient(ingredientsOfCategory[i]);
		}
		previewListPanel->ingredientSizer->Add(0, skipLine);
		ingredientsOfCategory.clear();
	}
	
	previewListWin->ShowModal();
}
void MainScrollPanel::LeftDateArrowPressed(wxCommandEvent& WXUNUSED(event)) {
	date = dateHandler.getNewDate(date, "decrease");
	std::string dateLabel = std::to_string(date.month) + "/" + std::to_string(date.day) + "/" + std::to_string(date.year);
	Date->SetLabelText(dateLabel);
	generateMealClicks = 0;
	updateMealOfTheDay();
}
void MainScrollPanel::RightDateArrowPressed(wxCommandEvent& WXUNUSED(event)) {
	date = dateHandler.getNewDate(date, "increase");
	std::string dateLabel = std::to_string(date.month) + "/" + std::to_string(date.day) + "/" + std::to_string(date.year);
	Date->SetLabelText(dateLabel);
	generateMealClicks = 0;
	updateMealOfTheDay();
}
void MainScrollPanel::LeftRangeArrowPressed(wxCommandEvent& WXUNUSED(event)) {
	int range = wxAtoi(Range->GetLabelText());
	if (range > 1) {
		Range->SetLabelText(std::to_string(range - 1));
	}
}
void MainScrollPanel::RightRangeArrowPressed(wxCommandEvent& WXUNUSED(event)) {
	int range = wxAtoi(Range->GetLabelText());
	Range->SetLabelText(std::to_string(range + 1));
}
void MainScrollPanel::MealTypeSpecificOrCategory(wxCommandEvent& WXUNUSED(event)) {
	if (MealType->GetSelection() == 1) {
		MealOrCategory->SetLabel(wxT("Pick Meal"));
		SelectedOrGeneratedMeal->SetLabel(wxT("Selected Meal: "));
		PickMealOrGenerateMeal->SetLabelText(wxT("Enter Meal"));
	}
	else if (this->MealType->GetSelection() == 0) {
		MealOrCategory->SetLabel(wxT("Pick Category"));
		SelectedOrGeneratedMeal->SetLabel(wxT("Generated Meal: "));
		PickMealOrGenerateMeal->SetLabelText(wxT("Generate Meal"));
	}
	updateMealsOrCategories();
	updateMealOfTheDayLabel();
	updatePickMealOrGenerateMeal();
	updateMealOrCategory();
}
void MainScrollPanel::PickMealOrGenerateMealPressed(wxCommandEvent& WXUNUSED(event)) {
	mealPicker mealHandler;
	int EnterMealOrEnterCategoryIndex = EnterMealOrEnterCategory->GetSelection();
	if (EnterMealOrEnterCategoryIndex != wxNOT_FOUND) {
		wxString mealNameOrCategory = EnterMealOrEnterCategory->GetString(EnterMealOrEnterCategoryIndex);
		if (PickMealOrGenerateMeal->GetLabelText() == "Enter Meal") {
			item.mealName = mealNameOrCategory;
			item.date = date;
			foodPlannerData.setChosenMeal(item);
			fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
		}
		else if (PickMealOrGenerateMeal->GetLabelText() == "Generate Meal") {
			item.mealName = mealHandler.pickMeal(std::string(mealNameOrCategory.mb_str()), generateMealClicks, date);
			item.date = date;
			foodPlannerData.setChosenMeal(item);
			fileReaderWriter.write_file(test_path, fileReaderWriter.Stringify(foodPlannerData));
			generateMealClicks++;
		}
		updateDisplayedChosenMeals();
		updateMealOfTheDay();
	}
	else {
		wxMessageBox("Enter a meal or category.");
	}
}
void MainScrollPanel::CategoryPicked(wxCommandEvent& WXUNUSED(event)) {
	if (PickMealOrGenerateMeal->GetLabelText() == "Generate Meal") {
		generateMealClicks = 0;
	}
}
void MainScrollPanel::EnterRangePressed(wxCommandEvent& WXUNUSED(event)) {
	rangeDate = date;
	updateDisplayedChosenMeals();
	beginDate = date;
	endDate = date;
	for (int i = 0; i < displayChosenMealInfoGroups.size(); i++) {
		endDate = dateHandler.getNewDate(endDate, "increase");
	}
}

void MainFrame::CheckForClose(wxShowEvent&) {

}
void MainFrame::CloseFrame(wxCloseEvent& event) {
	wxGetApp().ExitMainLoop();
}