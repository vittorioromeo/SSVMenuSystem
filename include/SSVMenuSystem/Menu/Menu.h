// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>
#include <memory>

namespace ssvms
{
	class ItemBase;
	class Category;
	namespace Items { class Goto; }

	class Menu
	{
		friend class Category;
		friend class Items::Goto;

		private:
			std::vector<std::unique_ptr<ItemBase>> items; // owned
			std::vector<std::unique_ptr<Category>> categories; // owned
			Category* currentCategory{nullptr};

			template<typename T, typename... TArgs> T& create(Category& mCategory, const std::string& mName, TArgs&&... mArgs)
			{
				T* result{new T(*this, mCategory, mName, std::forward<TArgs>(mArgs)...)};
				items.push_back(std::unique_ptr<T>(result));
				return *result;
			}

			void setCurrentCategory(Category& mCategory);

		public:
			Menu() = default;
			~Menu();

			Category& createCategory(const std::string& mName);
			void clear();

			void selectNextItem();
			void selectPreviousItem();
			void executeCurrentItem();
			void increaseCurrentItem();
			void decreaseCurrentItem();

			Category& getCurrentCategory();
			ItemBase& getCurrentItem();
			std::vector<ItemBase*>& getCurrentItems();
			int getCurrentIndex();
	};
}

#endif
