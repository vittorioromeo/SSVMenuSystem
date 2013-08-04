// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_CATEGORY
#define SSVMS_CATEGORY

#include <vector>
#include <string>

namespace ssvms
{
	class Menu;
	class ItemBase;

	class Category
	{
		friend class Menu;

		private:
			Menu& menu;
			std::string name;
			std::vector<std::unique_ptr<ItemBase>> items;
			int currentIndex{0};

			inline void wrapIndex()
			{
				if(items.empty()) { currentIndex = -1; return; }
				else if(currentIndex > static_cast<int>(items.size() - 1)) currentIndex = 0;
				else if(currentIndex < 0) currentIndex = items.size() - 1;
			}

		public:
			Category(Menu& mMenu, const std::string& mName) : menu(mMenu), name{mName} { }

			template<typename T, typename... TArgs> T& create(const std::string& mName, TArgs&&... mArgs)
			{
				T* result{new T(menu, *this, mName, std::forward<TArgs>(mArgs)...)};
				items.push_back(std::unique_ptr<T>(result));
				return *result;
			}

			inline void selectNextItem()				{ ++currentIndex; wrapIndex(); }
			inline void selectPreviousItem()			{ --currentIndex; wrapIndex(); }

			inline const std::string& getName()			{ return name; }
			inline ItemBase& getCurrentItem()			{ return *(items[currentIndex]); }
			inline std::vector<std::unique_ptr<ItemBase>>& getItems()	{ return items; }
			inline int getCurrentIndex()				{ return currentIndex; }
	};
}

#endif
