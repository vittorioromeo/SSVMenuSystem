#include "Toggle.h"

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

