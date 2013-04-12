// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_CATEGORY
#define SSVMS_CATEGORY

#include <vector>
#include <string>
#include "SSVMenuSystem/Menu/Menu.h"

namespace ssvms
{
	class ItemBase;

	class Category
	{
		friend class Menu;

		private:
			Menu& menu;
			std::string name;
			std::vector<ItemBase*> items;
			int currentIndex{0};

			void wrapIndex();

		public:
			Category(Menu& mMenu, const std::string& mName);

			template<typename T, typename... TArgs> T& create(const std::string& mName, TArgs&&... mArgs)
			{
				T& result(menu.create<T>(*this, mName, (mArgs)...));
				items.push_back(&result);
				return result;
			}

			void selectNextItem();
			void selectPreviousItem();

			const std::string& getName();
			ItemBase& getCurrentItem();
			std::vector<ItemBase*>& getItems();
			int getCurrentIndex();
	};
}

#endif
