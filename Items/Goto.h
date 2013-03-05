#ifndef SSVMS_ITEM_GOTO
#define SSVMS_ITEM_GOTO

#include "ItemBase.h"

namespace ssvms
{
	class Menu;
	class Category;

	namespace Items
	{
		class Goto : public ItemBase
		{
			private:
				Category& targetCategory;

			public:
				Goto(Menu& mMenu, Category& mCategory, const std::string& mName, Category& mTargetCategory);
				void execute() override;
		};
	}
}

#endif
