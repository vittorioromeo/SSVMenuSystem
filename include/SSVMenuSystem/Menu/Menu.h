// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>
#include <memory>
#include <stack>
#include "SSVMenuSystem/Menu/ItemBase.h"
#include "SSVMenuSystem/Menu/Category.h"

namespace ssvms
{
	class Category;
	namespace Items
	{
		class Goto;
	}

	class Menu
	{
		friend class Category;
		friend class Items::Goto;

		private:
			std::vector<std::unique_ptr<Category>> categories;
			Category* category{nullptr};
			std::stack<Category*> lastCategories;

			inline void setCategory(Category& mCategory)
			{
				lastCategories.push(&mCategory);
				category = &mCategory;
			}

		public:
			inline Category& createCategory(const std::string& mName)
			{
				Category* result{new Category{*this, mName}};
				categories.emplace_back(result);
				if(category == nullptr) setCategory(*result);
				return *result;
			}
			inline void clear()		{ categories.clear(); }
			inline void goBack()	{ lastCategories.pop(); category = lastCategories.top(); }

			inline void next()		{ category->next(); }
			inline void previous()	{ category->previous(); }
			inline void exec()		{ if(getItem().isEnabled()) getItem().exec(); }
			inline void increase()	{ if(getItem().isEnabled()) getItem().increase(); }
			inline void decrease()	{ if(getItem().isEnabled()) getItem().decrease(); }

			inline bool canGoBack() const											{ return lastCategories.size() > 1; }
			inline Category& getCategory() const									{ return *category; }
			inline ItemBase& getItem() const										{ return category->getItem(); }
			inline const std::vector<std::unique_ptr<ItemBase>>& getItems() const	{ return category->getItems(); }
			inline int getIndex() const												{ return category->getIndex(); }
	};
}

#endif
