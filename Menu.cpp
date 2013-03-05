#include "Menu.h"
#include "Category.h"
#include "ItemBase.h"

using namespace std;

namespace ssvms
{
	Menu::~Menu() { clear(); }

	Category& Menu::createCategory(const string& mName)
	{
		Category* result{new Category{*this, mName}};
		categories.push_back(result);		
		if(currentCategory == nullptr) currentCategory = result;
		return *result;
	}
	void Menu::clear()
	{
		for(auto& item : items) delete item;
		for(auto& category : categories) delete category;
		items.clear();
		categories.clear();
	}

	void Menu::selectNextItem() { currentCategory->selectNextItem(); }
	void Menu::selectPreviousItem() { currentCategory->selectPreviousItem(); }
	void Menu::executeCurrentItem() { getCurrentItem().execute(); }
	void Menu::increaseCurrentItem() { getCurrentItem().increase(); }
	void Menu::decreaseCurrentItem() { getCurrentItem().decrease(); }

	void Menu::setCurrentCategory(Category& mCategory) { currentCategory = &mCategory; }
	Category& Menu::getCurrentCategory() { return *currentCategory; }
	ItemBase& Menu::getCurrentItem() { return currentCategory->getCurrentItem(); }
	vector<ItemBase*>& Menu::getCurrentItems() { return currentCategory->getItems(); }
	int Menu::getCurrentItemsIndex() { return currentCategory->getCurrentIndex(); }
}

