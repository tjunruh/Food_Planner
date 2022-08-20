#include "Food_Planner.h"

SavedInfo foodPlannerData;

void SavedInfo::setMeal(Meal item) {
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == item.Name) {
			meal.erase(meal.begin() + i);
			break;
		}
	}
	meal.push_back(item);

}

void SavedInfo::setList(List item) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].StoreName == item.StoreName) {
			list.erase(list.begin() + i);
			break;
		}
	}
	list.push_back(item);
}

//SavedInfo setIngredient(SavedInfo info, Ingredient item, std::string mealName) {
//	for (int i = 0; i < info.meal.size(); i++) {
//		if (info.meal[i].Name == mealName) {
//			info.meal[i].Ingredients.push_back(item);
//			break;
//		}
//	}
//
//	return info;
//}

//SavedInfo JSON::setMealIngredient(SavedInfo info, Ingredient item, std::string mealName) {
//	Meal selectMeal;
//	for (int i = 0; i < info.meal.size(); i++) {
//		if (info.meal[i].Name == mealName) {
//			selectMeal = info.meal[i];
//			selectMeal.Ingredients.push_back(item);
//			info = setMeal(info, selectMeal);
//			break;
//		}
//	}

//	return info;
//}

//SavedInfo JSON::setMealCategory(SavedInfo info, std::string item, std::string mealName) {
//	Meal selectMeal;
//	for (int i = 0; i < info.meal.size(); i++) {
//		if (info.meal[i].Name == mealName) {
//			selectMeal = info.meal[i];
//			for (int i = 0; i < selectMeal.Categories.size(); i++) {
//				if (selectMeal.Categories[i] == item) {
//					selectMeal.Categories.erase(selectMeal.Categories.begin() + i);
//					break;
//				}
//			}
//			selectMeal.Categories.push_back(item);
//			info = setMeal(info, selectMeal);
//			break;
//		}
//	}

//	return info;
//}

void SavedInfo::setMealName(std::string newName, std::string oldName) {
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == oldName) {
			meal[i].Name = newName;
			break;
		}
	}
}

void SavedInfo::setListStoreName(std::string newName, std::string oldName) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].StoreName == oldName) {
			list[i].StoreName = newName;
			break;
		}
	}
}

//SavedInfo JSON::setListIngredientCategory(SavedInfo info, std::string item, std::string storeName) {
//	List selectList;
//	for (int i = 0; i < info.list.size(); i++) {
//		if (info.list[i].StoreName == storeName) {
//			selectList = info.list[i];
//			for (int i = 0; i < selectList.IngredientCategories.size(); i++) {
//				if (selectList.IngredientCategories[i] == item) {
//					selectList.IngredientCategories.erase(selectList.IngredientCategories.begin() + i);
//					break;
//				}
//			}
//			selectList.IngredientCategories.push_back(item);
//			info = setList(info, selectList);
//			break;
//		}
//	}

//	return info;
//}

//SavedInfo JSON::setListOrder(SavedInfo info, std::string item, std::string storeName, int position) {
//	List selectList;
//	for (int i = 0; i < info.list.size(); i++) {
//		if (info.list[i].StoreName == storeName) {
//			selectList = info.list[i];
//			for (int i = 0; i < selectList.Order.size(); i++) {
//				if (selectList.Order[i] == item) {
//					selectList.Order.erase(selectList.Order.begin() + i - 1);
//					break;
//				}
//			}
//			selectList.Order.insert(selectList.Order.begin() + position - 1, item);
//			info = setList(info, selectList);
//			break;
//		}
//	}

//	return info;
//}

void SavedInfo::setMealCategories(std::vector<std::string> categories) {
	mealCategories.clear();
	mealCategories = categories;
}

void SavedInfo::setStoreCategories(std::vector<std::string> categories) {
	storeCategories.clear();
	storeCategories = categories;
}

void SavedInfo::setPantryCategories(std::vector<std::string> categories) {
	pantryCategories.clear();
	pantryCategories = categories;
}
//SavedInfo JSON::setOverallMealCategories(SavedInfo info, std::vector<std::string> item) {
//	info.categories.mealCategories = item;
//	return info;
//}

//SavedInfo JSON::setOverallIngredientCategories(SavedInfo info, std::vector<std::string> item) {
//	info.categories.ingredientCategories = item;
//	return info;
//}

void SavedInfo::setUnits(std::vector<std::string> unitsInput) {
	units.clear();
	units = unitsInput;
}

void SavedInfo::setIngredientNames(std::vector<std::string> names) {
	ingredientNames.clear();
	ingredientNames = names;
}

void SavedInfo::setChosenMeal(ChosenMeal item) {
	for (int i = 0; i < chosenmeal.size(); i++) {
		if ((item.date.day == chosenmeal[i].date.day) && (item.date.month == chosenmeal[i].date.month) && (item.date.year == chosenmeal[i].date.year)) {
			chosenmeal.erase(chosenmeal.begin() + i);
			break;
		}
	}
	chosenmeal.push_back(item);
}

std::vector<wxString> SavedInfo::getIngredientCategories() {
	std::vector<wxString> categories;
	for (int i = 0; i < storeCategories.size(); i++) {
		categories.push_back(storeCategories[i]);
	}
	return categories;
}

std::vector<wxString> SavedInfo::getMealCategories() {
	std::vector<wxString> categories;
	for (int i = 0; i < mealCategories.size(); i++) {
		categories.push_back(mealCategories[i]);
	}
	return categories;
}

std::vector<wxString> SavedInfo::getPantryCategories() {
	std::vector<wxString> categories;
	for (int i = 0; i < pantryCategories.size(); i++) {
		categories.push_back(pantryCategories[i]);
	}
	return categories;
}

std::vector<wxString> SavedInfo::getUnits() {
	std::vector<wxString> returnUnits;
	for (int i = 0; i < units.size(); i++) {
		returnUnits.push_back(units[i]);
	}
	return returnUnits;
}

std::vector<wxString> SavedInfo::getOrder() {
	std::vector<wxString> order;
	for (int i = 0; i < storeCategories.size(); i++) {
		order.push_back(std::to_string(i + 1));
	}
	return order;
}
std::vector<wxString> SavedInfo::getMealNames() {
	std::vector<wxString> names;
	for (int i = 0; i < meal.size(); i++) {
		names.push_back(meal[i].Name);
	}
	return names;
}

std::vector<std::string> SavedInfo::getMealCategoriesOfMeal(std::string mealName) {
	std::vector<std::string> categories;
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == mealName) {
			categories = meal[i].Categories;
			break;
		}
	}
	return categories;
}

std::vector<wxString> SavedInfo::getListStoreNames() {
	std::vector<wxString> names;
	for (int i = 0; i < list.size(); i++) {
		names.push_back(list[i].StoreName);
	}
	return names;
}

std::vector<wxString> SavedInfo::getIngredientNames() {
	std::vector<wxString> names;
	for (int i = 0; i < ingredientNames.size(); i++) {
		names.push_back(ingredientNames[i]);
	}
	return names;
}

Meal SavedInfo::getMeal(std::string mealName) {
	Meal item;
	item.Name = "";
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == mealName) {
			item = meal[i];
			break;
		}
	}
	return item;
}

std::vector<Meal> SavedInfo::getMeals() {
	return meal;
}

std::vector<std::string> SavedInfo::getMealNamesOfCategory(std::string category) {
	std::vector<std::string> mealsOfCategory;
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Categories.size(); j++) {
			if (meal[i].Categories[j] == category) {
				mealsOfCategory.push_back(meal[i].Name);
			}
		}
	}
	return mealsOfCategory;
}

std::vector<std::string> SavedInfo::getIngredientNamesOfStoreCategory(std::string category) {
	std::vector<std::string> ingredientsOfCategory;
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].storeCategory == category) {
				for (int k = 0; k < ingredientsOfCategory.size(); k++) {
					if (meal[i].Ingredients[j].Name == ingredientsOfCategory[k]) {
						ingredientsOfCategory.erase(ingredientsOfCategory.begin() + k);
					}
				}
				ingredientsOfCategory.push_back(meal[i].Ingredients[j].Name);
			}
		}
	}
	return ingredientsOfCategory;
}

std::vector<std::string> SavedInfo::getIngredientNamesOfPantryCategory(std::string category) {
	std::vector<std::string> ingredientsOfCategory;
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].pantryCategory == category) {
				for (int k = 0; k < ingredientsOfCategory.size(); k++) {
					if (meal[i].Ingredients[j].Name == ingredientsOfCategory[k]) {
						ingredientsOfCategory.erase(ingredientsOfCategory.begin() + k);
					}
				}
				ingredientsOfCategory.push_back(meal[i].Ingredients[j].Name);
			}
		}
	}
	return ingredientsOfCategory;
}

std::vector<std::string> SavedInfo::getIngredientNamesOfUnit(std::string unit) {
	std::vector<std::string> ingredientsOfUnit;
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].Unit == unit) {
				for (int k = 0; k < ingredientsOfUnit.size(); k++) {
					if (meal[i].Ingredients[j].Name == ingredientsOfUnit[k]) {
						ingredientsOfUnit.erase(ingredientsOfUnit.begin() + k);
					}
				}
				ingredientsOfUnit.push_back(meal[i].Ingredients[j].Name);
			}
		}
	}
	return ingredientsOfUnit;
}

List SavedInfo::getList(std::string storeName) {
	List item;
	for (int i = 0; i < list.size(); i++) {
		if (list[i].StoreName == storeName) {
			item = list[i];
			break;
		}
	}
	return item;
}

ChosenMeal SavedInfo::getChosenMeal(monthDayYear dateInput) {
	ChosenMeal item;
	for (int i = 0; i < chosenmeal.size(); i++) {
		if ((chosenmeal[i].date.day == dateInput.day) && (chosenmeal[i].date.month == dateInput.month) && (chosenmeal[i].date.year == dateInput.year)) {
			item = chosenmeal[i];
		}
	}
	return item;
}

ChosenMeal SavedInfo::getChosenMeal(std::string name) {
	ChosenMeal item;
	for (int i = 0; i < chosenmeal.size(); i++) {
		if (chosenmeal[i].mealName == name) {
			item = chosenmeal[i];
			break;
		}
	}
	return item;
}

std::vector<ChosenMeal> SavedInfo::getChosenMeals() {
	return chosenmeal;
}

bool SavedInfo::findUnit(wxString unit) {
	bool found = false;
	for (int i = 0; i < units.size(); i++) {
		if (units[i] == unit) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findMealCategory(wxString category) {
	bool found = false;
	for (int i = 0; i < mealCategories.size(); i++) {
		if (mealCategories[i] == category) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findIngredientStoreCategory(wxString category) {
	bool found = false;
	for (int i = 0; i < storeCategories.size(); i++) {
		if (storeCategories[i] == category) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findIngredientPantryCategory(wxString category) {
	bool found = false;
	for (int i = 0; i < pantryCategories.size(); i++) {
		if (pantryCategories[i] == category) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findIngredientName(wxString name) {
	bool found = false;
	for (int i = 0; i < ingredientNames.size(); i++) {
		if (ingredientNames[i] == name) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findMeal(wxString mealName) {
	bool found = false;
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == mealName) {
			found = true;
			break;
		}
	}
	return found;
}

bool SavedInfo::findList(wxString listName) {
	bool found = false;
	for (int i = 0; i < list.size(); i++) {
		if (list[i].StoreName == listName) {
			found = true;
			break;
		}
	}
	return found;
}

void SavedInfo::deleteMeal(std::string mealName) {
	for (int i = 0; i < meal.size(); i++) {
		if (meal[i].Name == mealName) {
			meal.erase(meal.begin() + i);
			break;
		}
	}
}

void SavedInfo::deleteList(std::string storeName) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].StoreName == storeName) {
			list.erase(list.begin() + i);
			break;
		}
	}
}

void SavedInfo::renameMealCategory(std::string oldCategory, std::string newCategory) {
	for (int i = 0; i < mealCategories.size(); i++) {
		if (mealCategories[i] == newCategory) {
			mealCategories.erase(mealCategories.begin() + i);
		}
		if (mealCategories[i] == oldCategory) {
			mealCategories[i] = newCategory;
		}
	}
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Categories.size(); j++) {
			if (meal[i].Categories[j] == oldCategory) {
				meal[i].Categories[j] == newCategory;
			}
		}
	}
}

void SavedInfo::renameIngredientStoreCategory(std::string oldCategory, std::string newCategory) {
	for (int i = 0; i < storeCategories.size(); i++) {
		if (storeCategories[i] == newCategory) {
			storeCategories.erase(storeCategories.begin() + i);
		}
		if (storeCategories[i] == oldCategory) {
			storeCategories[i] = newCategory;
		}
	}
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].storeCategory == oldCategory) {
				meal[i].Ingredients[j].storeCategory = newCategory;
			}
		}
	}
}

void SavedInfo::renameIngredientPantryCategory(std::string oldCategory, std::string newCategory) {
	for (int i = 0; i < pantryCategories.size(); i++) {
		if (pantryCategories[i] == newCategory) {
			pantryCategories.erase(pantryCategories.begin() + i);
		}
		if (pantryCategories[i] == oldCategory) {
			pantryCategories[i] = newCategory;
		}
	}
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].pantryCategory == oldCategory) {
				meal[i].Ingredients[j].pantryCategory == newCategory;
			}
		}
	}
}

void SavedInfo::renameIngredient(std::string oldName, std::string newName) {
	for (int i = 0; i < ingredientNames.size(); i++) {
		if (ingredientNames[i] == newName) {
			ingredientNames.erase(ingredientNames.begin() + i);
		}
		if (ingredientNames[i] == oldName) {
			ingredientNames[i] = newName;
		}
	}
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].Name == oldName) {
				meal[i].Ingredients[j].Name = newName;
			}
		}
	}
}

void SavedInfo::renameUnit(std::string oldUnit, std::string newUnit) {
	for (int i = 0; i < units.size(); i++) {
		if (units[i] == newUnit) {
			units.erase(units.begin() + i);
		}
		if (units[i] == oldUnit) {
			units[i] = newUnit;
		}
	}
	for (int i = 0; i < meal.size(); i++) {
		for (int j = 0; j < meal[i].Ingredients.size(); j++) {
			if (meal[i].Ingredients[j].Unit == oldUnit) {
				meal[i].Ingredients[j].Unit = newUnit;
			}
		}
	}
}
//void JSON::deleteMealIngredient(SavedInfo info, std::string mealName, std::string ingredientName) {
//	for (int i = 0; i < info.meal.size(); i++) {
//		if (info.meal[i].Name == mealName) {
//			for (int j = 0; j < info.meal[i].Ingredients.size(); j++) {
//				if (info.meal[i].Ingredients[j].Name == ingredientName) {
//					info.meal[i].Ingredients.erase(info.meal[i].Ingredients.begin() + j);
//					break;
//				}
//			}
//			break;
//		}
//	}
//}

//void JSON::deleteMealCategory(SavedInfo info, std::string mealName, std::string category) {
//	for (int i = 0; i < info.meal.size(); i++) {
//		if (info.meal[i].Name == mealName) {
//			for (int j = 0; j < info.meal[i].Categories.size(); j++) {
//				if (info.meal[i].Categories[j] == category) {
//					info.meal[i].Categories.erase(info.meal[i].Categories.begin() + j);
//				}
//			}
//		}
//	}
//}

//void JSON::deleteListCategoryAndOrder(SavedInfo info, std::string storeName, std::string category) {
//	for (int i = 0; i < info.list.size(); i++) {
//		if (info.list[i].StoreName == storeName) {
//			for (int j = 0; j < info.list[i].IngredientCategories.size(); j++) {
//				if (info.list[i].IngredientCategories[j] == category) {
//					info.list[i].IngredientCategories.erase(info.list[i].IngredientCategories.begin() + j);
//					break;
//				}
//			}

//			for (int k = 0; k < info.list[i].Order.size(); k++) {
//				if (info.list[i].Order[k] == category) {
//					info.list[i].Order.erase(info.list[i].Order.begin() + k);
//					break;
//				}
//			}
//			break;
//		}
//	}
//}

//void SavedInfo::deleteMealCategory(std::string category) {
//	for (int i = 0; i < mealCategories.size(); i++) {
//		if (mealCategories[i] == category) {
//			mealCategories.erase(mealCategories.begin() + i);
//			for (int j = 0; j < meal.size(); j++) {
//				for (int k = 0; k < meal[j].Categories.size(); k++) {
//					if (meal[j].Categories[k] == category) {
//						meal[j].Categories.erase(meal[j].Categories.begin() + k);
//					}
//				}
//			}
//		}
//	}
//}

//void SavedInfo::deleteIngredientCategory(std::string oldCategory, std::string newCategory) {
//	for (int i = 0; i < info.categories.ingredientCategories.size(); i++) {
//		if (info.categories.ingredientCategories[i] == oldCategory) {
//			info.categories.ingredientCategories.erase(info.categories.ingredientCategories.begin() + i);
//			for (int j = 0; j < info.meal.size(); j++) {
//				for (int k = 0; k < info.meal[j].Ingredients.size(); k++) {
//					if (info.meal[j].Ingredients[k].Category == oldCategory)
//						info.meal[j].Ingredients[k].Category == newCategory;
//				}
//			}
//		}
//	}
//}