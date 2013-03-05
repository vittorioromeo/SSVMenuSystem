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
			private:
				std::function<void()> action;

			public:
				Single(Menu& mMenu, Category& mCategory, const std::string& mName, std::function<void()> mAction);
				void execute() override;
		};
	}
}

#endif
