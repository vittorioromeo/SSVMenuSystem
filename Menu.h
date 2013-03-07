#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>

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
			std::vector<ItemBase*> items; // owned
			std::vector<Category*> categories; // owned
			Category* currentCategory{nullptr};
			
			template<typename T, typename... TArgs> T& create(Category& mCategory, const std::string& mName, TArgs&&... mArgs)
			{
				T* result{new T(*this, mCategory, mName, std::forward<TArgs>(mArgs)...)};
				items.push_back(result);
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
