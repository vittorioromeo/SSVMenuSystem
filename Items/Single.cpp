#include "Single.h"

using namespace std;

namespace ssvms
{
	namespace Items
	{
		Single::Single(Menu& mMenu, Category& mCategory, const string& mName, function<void()> mAction) : ItemBase{mMenu, mCategory, mName}, action{mAction} { }
		void Single::execute() { action(); }
	}
}

