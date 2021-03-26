// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_TOGGLE
#define SSVMS_ITEM_TOGGLE

#include "SSVMenuSystem/Global/Typedefs.hpp"
#include "SSVMenuSystem/Menu/ItemBase.hpp"
#include "SSVMenuSystem/Menu/Menu.hpp"

#include <string>

namespace ssvms
{
    class Menu;
    class Category;

    namespace Items
    {
        class Toggle final : public ItemBase
        {
        private:
            Predicate predicate;
            Action activateAction, deactivateAction;

        public:
            Toggle(Menu& mMenu, Category& mCategory, const std::string& mName,
                Predicate mActivatedPredicate, Action mActivateAction,
                Action mDeactivateAction)
                : ItemBase{mMenu, mCategory, mName},
                  predicate(mActivatedPredicate),
                  activateAction{mActivateAction},
                  deactivateAction{mDeactivateAction}
            {
                increasable = true;
            }

            template <typename TFuncGet, typename TFuncSet>
            Toggle(Menu& mMenu, Category& mCategory, const std::string& mName,
                TFuncGet mFuncGet, TFuncSet mFuncSet)
                : ItemBase{mMenu, mCategory, mName},
                  predicate{[=]
                      {
                          return mFuncGet();
                      }},
                  activateAction{[=]
                      {
                          mFuncSet(true);
                      }},
                  deactivateAction{[=]
                      {
                          mFuncSet(false);
                      }}
            {
                increasable = true;
            }

            Toggle(Menu& mMenu, Category& mCategory, const std::string& mName,
                bool& mBool)
                : ItemBase{mMenu, mCategory, mName},
                  predicate{[&mBool]
                      {
                          return mBool;
                      }},
                  activateAction{[&mBool]
                      {
                          mBool = true;
                      }},
                  deactivateAction{[&mBool]
                      {
                          mBool = false;
                      }}
            {
                increasable = true;
            }

            inline void exec() override
            {
                predicate() ? deactivateAction() : activateAction();
            }
            inline void increase() override
            {
                exec();
            }
            inline void decrease() override
            {
                exec();
            }
            inline std::string getName() const override
            {
                return predicate() ? name + ": on" : name + ": off";
            }
        };
    }
}

#endif
