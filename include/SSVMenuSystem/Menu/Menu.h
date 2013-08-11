// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

#include <vector>
#include <string>
#include <memory>
#include <stack>
#include <functional>
#include "SSVMenuSystem/Menu/ItemBase.h"
#include "SSVMenuSystem/Menu/Category.h"
#include "SSVMenuSystem/Menu/Controller.h"

namespace ssvms
{
	class Menu
	{
		friend class Category;

		private:
			using Controller = Internal::Controller;
			using Predicate = Internal::Controller::Predicate;

			std::vector<std::unique_ptr<Category>> categories;
			Category* category{nullptr};
			std::stack<Category*> lastCategories;
			Controller controller;

		public:
			inline Category& createCategory(const std::string& mName)
			{
				auto result(new Category{*this, mName});
				categories.emplace_back(result);
				if(category == nullptr) setCategory(*result);
				return *result;
			}
			inline void setCategory(Category& mCategory)
			{
				lastCategories.push(&mCategory);
				category = &mCategory;
			}

			inline void clear()		{ categories.clear(); }
			inline void update()	{ controller.update(); }

			// Navigation
			inline void goBack()	{ lastCategories.pop(); category = lastCategories.top(); }
			inline void next()		{ category->next(); }
			inline void previous()	{ category->previous(); }
			inline void exec()		{ if(getItem().isEnabled()) getItem().exec(); }
			inline void increase()	{ if(getItem().isEnabled()) getItem().increase(); }
			inline void decrease()	{ if(getItem().isEnabled()) getItem().decrease(); }

			inline bool canGoBack() const									{ return lastCategories.size() > 1; }
			inline Category& getCategory() const							{ return *category; }
			inline ItemBase& getItem() const								{ return category->getItem(); }
			inline const decltype(category->getItems())& getItems() const	{ return category->getItems(); }
			inline int getIndex() const										{ return category->getIndex(); }
			inline Internal::Controller& getMenuController()				{ return controller; }
	};

	// Pipe operator allows to set predicates to enable/disable menu items
	inline ItemBase& operator|(ItemBase& mLhs, Internal::Controller::Predicate mRhs) { mLhs.getMenu().getMenuController().enableItemWhen(mLhs, mRhs); return mLhs; }
}

#endif
