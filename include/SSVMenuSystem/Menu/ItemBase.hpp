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
        using KKey = sf::Keyboard::Key;
        using MBtn = sf::Mouse::Button;
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

        //only used for BindControl
        inline virtual bool erase() { return false; }
        inline virtual bool newBind(const KKey key = KKey::Unknown, const MBtn btn = MBtn::Left) { (void)(key); (void)(btn); return 0; }
        inline virtual bool isWaitingForBind() { return false; }

        inline void setEnabled(bool mEnabled) { enabled = mEnabled; }

        inline auto& getMenu() const { return menu; }
        inline virtual std::string getName() const { return name; }
        inline bool isEnabled() const { return enabled; }
    };
}

#endif
