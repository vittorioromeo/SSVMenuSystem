// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

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

			private:
				Action action;

			public:
				Single(Menu& mMenu, Category& mCategory, const std::string& mName, Action mAction);
				void execute() override;
		};
	}
}

#endif
