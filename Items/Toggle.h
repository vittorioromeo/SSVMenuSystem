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
			private:
				std::function<bool()> activatedPredicate;
				std::function<void()> activateAction, deactivateAction;
				bool activated;

			public:
				Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, std::function<bool()> mActivatedPredicate, std::function<void()> mActivateAction, std::function<void()> mDeactivateAction);
				void execute() override;
				std::string getName() override;
		};
	}
}

#endif
