// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_TOGGLE
#define SSVMS_ITEM_TOGGLE

#include <string>
#include <functional>
#include "SSVMenuSystem/Menu/ItemBase.h"

namespace ssvms
{
	class Menu;
	class Category;

	namespace Items
	{
		class Toggle : public ItemBase
		{
			private:
				using Action = std::function<void()>;
				using Predicate = std::function<bool()>;
				Predicate predicate;
				Action activateAction, deactivateAction;

			public:
				Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, Predicate mActivatedPredicate, Action mActivateAction, Action mDeactivateAction)
					: ItemBase{mMenu, mCategory, mName}, predicate(mActivatedPredicate), activateAction{mActivateAction}, deactivateAction{mDeactivateAction} { }

				inline void exec() override { predicate() ? deactivateAction() : activateAction(); }
				inline std::string getName() const override { return predicate() ? name + ": on" : name + ": off"; }
		};
	}
}

#endif
