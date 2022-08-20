#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Food_Planner_Data.h"

class alphabetize {

public:
	std::vector<wxString> alphabetizeVector(std::vector<wxString> labels);
	std::vector<std::string> alphabetizeVector(std::vector<std::string> labels);
	std::vector<Ingredient> alphabetizeVector(std::vector<Ingredient> ingredients);
	bool isHighestAlphabetical(std::vector<wxString> labels, wxString label);
	bool isHighestAlphabetical(std::vector<std::string> labels, std::string label);
	bool isHighestAlphabetical(std::vector<Ingredient> ingredients, Ingredient ingredient);
	int positionToInsert(std::vector<std::string> labels, std::string label);
	std::string toLowerString(std::string str);
	wxString toLowerString(wxString);
};

extern alphabetize labelOrganizer;