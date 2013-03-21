// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_GOTO
#define SSVMS_ITEM_GOTO

#include "SSVMenuSystem/Menu/ItemBase.h"

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
