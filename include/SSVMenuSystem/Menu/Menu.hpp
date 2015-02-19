// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

namespace ssvms
{
	class Menu
	{
		friend Category;

		private:
			using Controller = Impl::Controller;

			std::vector<std::unique_ptr<Category>> categories;
			Category* category{nullptr};
			std::stack<Category*> lastCategories;
			Controller controller;

		public:
			inline auto& createCategory(const std::string& mName)
			{
				auto& result(ssvu::getEmplaceUPtr<Category>(categories, *this, mName));
				if(category == nullptr) setCategory(result);
				return result;
			}
			inline void setCategory(Category& mCategory)
			{
				lastCategories.emplace(&mCategory);
				category = &mCategory;
			}

			inline void clear() noexcept	{ categories.clear(); }
			inline void update()			{ controller.update(); }

			inline bool canGoBack() const								{ return lastCategories.size() > 1; }
			inline auto& getCategory() const							{ return *category; }
			inline auto& getItem() const								{ return category->getItem(); }
			inline const decltype(category->items)& getItems() const	{ return category->getItems(); }
			inline int getIdx() const									{ return category->getIdx(); }
			inline auto& getMenuController()							{ return controller; }

			// Navigation
			inline void goBack()	{ lastCategories.pop(); category = lastCategories.top(); }
			inline void next()		{ category->next(); }
			inline void previous()	{ category->previous(); }
			inline void exec()		{ if(getItem().isEnabled()) getItem().exec(); }
			inline void increase()	{ if(getItem().isEnabled()) getItem().increase(); }
			inline void decrease()	{ if(getItem().isEnabled()) getItem().decrease(); }
	};

	// Pipe operator allows to set predicates to enable/disable menu items
	inline auto& operator|(ItemBase& mLhs, Predicate mRhs) { mLhs.getMenu().getMenuController().enableItemWhen(mLhs, mRhs); return mLhs; }
}

#endif
