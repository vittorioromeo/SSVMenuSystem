// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENU
#define SSVMS_MENU

#include "SSVMenuSystem/Global/Typedefs.hpp"

#include "SSVMenuSystem/Menu/Controller.hpp"
#include "SSVMenuSystem/Menu/Category.hpp"

#include <string>
#include <stack>

namespace ssvms
{
    class Menu
    {
        friend Category;

    private:
        using Controller = Impl::Controller;

        std::vector<UniquePtr<Category>> categories;
        Category* category{nullptr};
        std::stack<Category*> lastCategories;
        Controller controller;

    public:
        inline auto& createCategory(const std::string& mName)
        {
            categories.push_back(
                makeUnique<Category>(*this, mName));

            auto& result(*categories.back());

            if(category == nullptr) setCategory(result);
            return result;
        }
        inline void setCategory(Category& mCategory)
        {
            lastCategories.emplace(&mCategory);
            category = &mCategory;
        }

        inline void clear() noexcept { categories.clear(); }
        inline void update() { controller.update(); }

        inline bool canGoBack() const { return lastCategories.size() > 1; }
        inline Category& getCategory() const { return *category; }
        inline auto& getCategories() const { return categories; }
        inline auto& getCategoryByName(const std::string& mName) const
        {
            for(auto& c : categories)
            {
                if(c->getName() == mName)
                    return *c;
            }
            return *category;
        }
        inline ItemBase& getItem() const { return category->getItem(); }
        inline std::vector<UniquePtr<ItemBase>>& getItems()
        {
            return category->getItems();
        }
        inline const std::vector<UniquePtr<ItemBase>>& getItems() const
        {
            return category->getItems();
        }
        inline int getIdx() const { return category->getIdx(); }
        inline auto& getMenuController() { return controller; }

        // Navigation
        inline void goBack()
        {
            lastCategories.pop();
            category = lastCategories.top();
        }
        inline void next() { category->next(); }
        inline void previous() { category->previous(); }
        inline void exec()
        {
            if(getItem().isEnabled()) getItem().exec();
        }
        inline void increase()
        {
            if(getItem().isEnabled()) getItem().increase();
        }
        inline void decrease()
        {
            if(getItem().isEnabled()) getItem().decrease();
        }
    };

    // Pipe operator allows to set predicates to enable/disable menu items
    inline ItemBase& operator|(ItemBase& mLhs, Predicate mRhs)
    {
        mLhs.getMenu().getMenuController().enableItemWhen(mLhs, mRhs);
        return mLhs;
    }
}

#endif
