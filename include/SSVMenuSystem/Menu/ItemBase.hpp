// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEMBASE
#define SSVMS_ITEMBASE

#include <string>

namespace ssvms
{
    class Menu;
    class Category;

    class ItemBase
    {
    protected:
        Menu& menu;
        Category& category;
        std::string name;
        bool enabled{true};

    public:
        ItemBase(Menu& mMenu, Category& mCategory, const std::string& mName)
            : menu(mMenu), category(mCategory), name{mName}
        {
        }
        inline virtual ~ItemBase() {}

        inline virtual void exec() {}
        inline virtual void increase() {}
        inline virtual void decrease() {}

        inline void setEnabled(bool mEnabled) { enabled = mEnabled; }

        inline auto& getMenu() const { return menu; }
        inline virtual std::string getName() const { return name; }
        inline bool isEnabled() const { return enabled; }

        float xOffset{0.f};
    };
}

#endif
