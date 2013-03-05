#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>

namespace ssvms
{
	class ItemBase;
	class Category;

	class Menu
	{
		friend class Category;

		private:
			std::vector<ItemBase*> items; // owned
			std::vector<Category*> categories; // owned
			Category* currentCategory{nullptr};
			

			template<typename T, typename... TArgs> T& createItem(Category& mCategory, const std::string& mName, TArgs&&... mArgs)
			{
				ItemBase* result{new T(*this, mCategory, mName, std::forward<TArgs>(mArgs)...)};
				items.push_back(result);
				return *(static_cast<T*>(result));
			}

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

			void setCurrentCategory(Category& mCategory);
			Category& getCurrentCategory();
			ItemBase& getCurrentItem();
			std::vector<ItemBase*>& getCurrentItems();
			int getCurrentItemsIndex();
	};
}

#endif
