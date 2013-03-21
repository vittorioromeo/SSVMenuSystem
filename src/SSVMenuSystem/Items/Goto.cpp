// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVMenuSystem/Items/Goto.h"
#include "SSVMenuSystem/Menu/Menu.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Goto::Goto(Menu& mMenu, Category& mCategory, const string& mName, Category& mTargetCategory) : ItemBase{mMenu, mCategory, mName}, targetCategory(mTargetCategory) { }
		void Goto::execute() { menu.setCurrentCategory(targetCategory); }
	}
}

