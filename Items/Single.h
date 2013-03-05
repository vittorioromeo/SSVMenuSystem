#ifndef SSVMS_ITEM_SINGLE
#define SSVMS_ITEM_SINGLE

#include <functional>
#include "ItemBase.h"

namespace ssvms
{
	class Menu;
	class Category;

	namespace Items
	{
		class Single : public ItemBase
		{
			typedef std::function<void()> Action;
			typedef std::function<bool()> Predicate;

			private:
				Action action;

			public:
				Single(Menu& mMenu, Category& mCategory, const std::string& mName, Action mAction);
				void execute() override;
		};
	}
}

#endif
