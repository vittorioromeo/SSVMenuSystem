#include "ItemBase.h"

using namespace std;

namespace ssvms
{
	ItemBase::ItemBase(Menu& mMenu, Category& mCategory, const string& mName) : menu(mMenu), category(mCategory), name{mName} { }
	ItemBase::~ItemBase() { }

	void ItemBase::execute() { }
	void ItemBase::increase() { }
	void ItemBase::decrease() { }

	string ItemBase::getName() { return name; }
}

