#include "Goto.h"
#include "Menu.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Goto::Goto(Menu& mMenu, Category& mCategory, const string& mName, Category& mTargetCategory) : ItemBase{mMenu, mCategory, mName}, targetCategory(mTargetCategory) { }
		void Goto::execute() { menu.setCurrentCategory(targetCategory); }
	}
}

