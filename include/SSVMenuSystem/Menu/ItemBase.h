// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEMBASE
#define SSVMS_ITEMBASE

#include <string>

namespace ssvms
{
	class Menu;
	class Category;

	class ItemBase
	{
		protected:
			Menu& menu;
			Category& category;
			std::string name;

		public:
			ItemBase(Menu& mMenu, Category& mCategory, const std::string& mName) : menu(mMenu), category(mCategory), name{mName} { }
			virtual ~ItemBase() { }

			virtual void execute() { }
			virtual void increase() { }
			virtual void decrease() { }

			virtual std::string getName() { return name; }
	};
}

#endif
