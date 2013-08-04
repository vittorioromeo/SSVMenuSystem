// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>
#include <memory>
#include "SSVMenuSystem/Menu/Category.h"
#include "SSVMenuSystem/Menu/ItemBase.h"

namespace ssvms
{
	class Category;
	namespace Items { class Goto; }

	class Menu
	{
		friend class Category;
		friend class Items::Goto;

		private:
			std::vector<std::unique_ptr<Category>> categories;
			Category* currentCategory{nullptr};

			void setCurrentCategory(Category& mCategory) { currentCategory = &mCategory; }

		public:
			Category& createCategory(const std::string& mName)
			{
				Category* result{new Category{*this, mName}};
				categories.emplace_back(result);
				if(currentCategory == nullptr) currentCategory = result;
				return *result;
			}
			void clear() { categories.clear(); }

			void selectNextItem() { currentCategory->selectNextItem(); }
			void selectPreviousItem() { currentCategory->selectPreviousItem(); }
			void executeCurrentItem() { getCurrentItem().execute(); }
			void increaseCurrentItem() { getCurrentItem().increase(); }
			void decreaseCurrentItem() { getCurrentItem().decrease(); }

			inline Category& getCurrentCategory() 				{ return *currentCategory; }
			inline ItemBase& getCurrentItem() 					{ return currentCategory->getCurrentItem(); }
			inline std::vector<std::unique_ptr<ItemBase>>& getCurrentItems() 	{ return currentCategory->getItems(); }
			inline int getCurrentIndex() 						{ return currentCategory->getCurrentIndex(); }
	};
}

#endif
