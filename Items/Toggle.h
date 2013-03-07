#ifndef SSVMS_ITEM_TOGGLE
#define SSVMS_ITEM_TOGGLE

#include <string>
#include <functional>
#include "ItemBase.h"

namespace ssvms
{
	class Menu;
	class Category;

	namespace Items
	{
		class Toggle : public ItemBase
		{
			typedef std::function<void()> Action;
			typedef std::function<bool()> Predicate;

			private:
				Predicate predicate;
				Action activateAction, deactivateAction;

			public:
				Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, Predicate mActivatedPredicate, Action mActivateAction, Action mDeactivateAction);
				void execute() override;
				std::string getName() override;
		};
	}
}

#endif
