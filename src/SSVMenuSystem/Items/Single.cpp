// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVMenuSystem/Items/Single.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Single::Single(Menu& mMenu, Category& mCategory, const string& mName, Action mAction) : ItemBase{mMenu, mCategory, mName}, action{mAction} { }
		void Single::execute() { action(); }
	}
}

