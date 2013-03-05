#include "Category.h"

using namespace std;

namespace ssvms
{
	Category::Category(Menu& mMenu, const string& mName) : menu(mMenu), name{mName} { }

	void Category::selectNextItem()
	{
		if(items.empty()) return;
		++currentIndex;

		if(currentIndex > (int)(items.size() - 1)) currentIndex = 0;
		else if(currentIndex < 0) currentIndex = items.size() - 1;
	}
	void Category::selectPreviousItem()
	{
		if(items.empty()) return;
		--currentIndex;

		if(currentIndex > (int)(items.size() - 1)) currentIndex = 0;
		else if(currentIndex < 0) currentIndex = items.size() - 1;
	}

	string Category::getName() { return name; }
	ItemBase& Category::getCurrentItem() { return *(items[currentIndex]); }
	vector<ItemBase*>& Category::getItems() { return items; }
	int Category::getCurrentIndex() { return currentIndex; }
}

