// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_GOBACK
#define SSVMS_ITEM_GOBACK

#include "SSVMenuSystem/Global/Typedefs.hpp"
#include "SSVMenuSystem/Menu/ItemBase.hpp"
#include "SSVMenuSystem/Menu/Menu.hpp"

#include <string>

namespace ssvms
{
    class Category;

    namespace Items
    {
        struct GoBack final : public ItemBase
        {
            GoBack(Menu& mMenu, Category& mCategory, const std::string& mName)
                : ItemBase{mMenu, mCategory, mName}
            {
            }
            inline void exec() override { menu.goBack(); }
        };
    }
}

#endif
