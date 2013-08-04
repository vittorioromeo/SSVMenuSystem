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
			private:
				using Action = std::function<void()>;
				using ValueGetter = std::function<std::string()>;
				ValueGetter valueGetter;
				Action increaseAction, decreaseAction;

			public:
				Slider(Menu& mMenu, Category& mCategory, const std::string& mName, ValueGetter mValueGetter, Action mIncreaseAction, Action mDecreaseAction)
					: ItemBase{mMenu, mCategory, mName}, valueGetter{mValueGetter}, increaseAction{mIncreaseAction}, decreaseAction{mDecreaseAction} { }

				inline void increase() override { increaseAction(); }
				inline void decrease() override { decreaseAction(); }
				inline std::string getName() override { return name + ": " + valueGetter(); }
		};
	}
}

#endif
