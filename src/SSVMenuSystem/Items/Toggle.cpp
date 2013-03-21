// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "SSVMenuSystem/Items/Toggle.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Toggle::Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, Predicate mActivatedPredicate, Action mActivateAction, Action mDeactivateAction)
			: ItemBase{mMenu, mCategory, mName}, predicate(mActivatedPredicate), activateAction{mActivateAction}, deactivateAction{mDeactivateAction} { }
		
		void Toggle::execute() { predicate() ? deactivateAction() : activateAction(); }
		string Toggle::getName() { return predicate() ? name + ": on" : name + ": off"; }
	}
}

