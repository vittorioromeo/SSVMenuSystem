#include "Toggle.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Toggle::Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, Predicate mActivatedPredicate, Action mActivateAction, Action mDeactivateAction)
			: ItemBase{mMenu, mCategory, mName}, predicate(mActivatedPredicate), activateAction{mActivateAction}, deactivateAction{mDeactivateAction},
			activated{predicate} { }
		
		void Toggle::execute()
		{
			activated = predicate();
			activated ? deactivateAction() : activateAction();
			activated = predicate();
		}
		string Toggle::getName() { return activated ? name + ": on" : name + ": off"; }
	}
}

