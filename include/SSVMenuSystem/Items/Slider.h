// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_SLIDER
#define SSVMS_ITEM_SLIDER

#include <functional>
#include <string>
#include "SSVMenuSystem/Menu/ItemBase.h"

namespace ssvms
{
	class Menu;
	class Category;

	namespace Items
	{
		class Slider : public ItemBase
		{
			typedef std::function<void()> Action;
			typedef std::function<std::string()> ValueGetter;

			private:
				ValueGetter valueGetter;
				Action increaseAction, decreaseAction;

			public:
				Slider(Menu& mMenu, Category& mCategory, const std::string& mName, ValueGetter mValueGetter, Action mIncreaseAction, Action mDecreaseAction);
				void increase() override;
				void decrease() override;
				std::string getName() override;
		};
	}
}

#endif // SSVMS_ITEM_SLIDER
