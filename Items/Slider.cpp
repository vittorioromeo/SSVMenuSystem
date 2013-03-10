// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "Slider.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Slider::Slider(Menu& mMenu, Category& mCategory, const string& mName, ValueGetter mValueGetter, Action mIncreaseAction, Action mDecreaseAction)
			: ItemBase{mMenu, mCategory, mName}, valueGetter{mValueGetter}, increaseAction{mIncreaseAction}, decreaseAction{mDecreaseAction} { }

		void Slider::increase() { increaseAction(); }
		void Slider::decrease() { decreaseAction(); }
		string Slider::getName() { return name + ": " + valueGetter(); }		
	}
}
