#include "Category.h"

using namespace std;

namespace ssvms
{
	Category::Category(Menu& mMenu, const string& mName) : menu(mMenu), name{mName} { }

	void Category::selectNextItem() 	{ ++currentIndex; wrapIndex(); }
	void Category::selectPreviousItem() { --currentIndex; wrapIndex(); }
	void Category::wrapIndex()
	{
		if(items.empty()) { currentIndex = -1; return; }
		else if(currentIndex > (int)(items.size() - 1)) currentIndex = 0;
		else if(currentIndex < 0) currentIndex = items.size() - 1;
	}

	string Category::getName() 				{ return name; }
	ItemBase& Category::getCurrentItem() 	{ return *(items[currentIndex]); }
	vector<ItemBase*>& Category::getItems() { return items; }
	int Category::getCurrentIndex() 		{ return currentIndex; }
}

