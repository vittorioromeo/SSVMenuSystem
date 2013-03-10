// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

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

