#include "Toggle.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Toggle::Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, std::function<bool()> mActivatedPredicate, std::function<void()> mActivateAction,
			std::function<void()> mDeactivateAction) : ItemBase{mMenu, mCategory, mName}, activatedPredicate(mActivatedPredicate),
			activateAction{mActivateAction}, deactivateAction{mDeactivateAction}, activated{activatedPredicate()} { }

		void Toggle::execute()
		{
			activated = activatedPredicate();
			activated ? deactivateAction() : activateAction();
			activated = activatedPredicate();
		}
		string Toggle::getName() { return activated ? name + ": on" : name + ": off"; }
	}
}

