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
