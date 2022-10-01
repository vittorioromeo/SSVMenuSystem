// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_CATEGORY
#define SSVMS_CATEGORY

#include "SSVMenuSystem/Global/Typedefs.hpp"

#include <SSVUtils/Core/Common/Casts.hpp>

#include <string>
#include <vector>

namespace ssvms
{
    class Menu;
    class ItemBase;

    class Category
    {
        friend Menu;

    private:
        Menu& menu;
        std::string name;
        std::vector<UniquePtr<ItemBase>> items;
        int index{0};
        float offset{0.f};

        inline void wrapIndex()
        {
            if(index > ssvu::toInt(items.size() - 1))
                index = 0;
            else if(index < 0)
                index = items.size() - 1;
        }

    public:
        Category(Menu& mMenu, const std::string& mName)
            : menu(mMenu), name{mName}
        {
        }

        template <typename T, typename... TArgs>
        inline T& create(const std::string& mName, TArgs&&... mArgs)
        {
            items.push_back(
                makeUniqueBase<ItemBase, T>(menu, *this, mName, FWD(mArgs)...));
            return static_cast<T&>(*items.back());
        }

        inline void remove()
        {
            items.erase(items.begin() + index);
            index = std::min(index, int(items.size()) - 1);
        }
        inline void sortByName()
        {
            auto sortFunc = [](const UniquePtr<ItemBase>& a, const UniquePtr<ItemBase>& b) -> bool
            {
                return a->getName() < b->getName();
            };
            std::sort(items.begin(), items.end(), sortFunc);
        }

        inline void next()
        {
            ++index;
            wrapIndex();
        }
        inline void previous()
        {
            --index;
            wrapIndex();
        }

        inline const auto& getName() const { return name; }
        inline auto& getItem() const { return *(items[index]); }
        inline auto& getItems() { return items; }
        inline const auto& getItems() const { return items; }
        inline int getIdx() const { return index; }
        inline float& getOffset() { return offset; }
    };
}

#endif
