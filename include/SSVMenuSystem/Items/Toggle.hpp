// Copyright (c) 2013-2014 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_TOGGLE
#define SSVMS_ITEM_TOGGLE

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
				Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, Predicate mActivatedPredicate, Action mActivateAction, Action mDeactivateAction)
					: ItemBase{mMenu, mCategory, mName}, predicate(mActivatedPredicate), activateAction{mActivateAction}, deactivateAction{mDeactivateAction} { }

				template<typename TFuncGet, typename TFuncSet> Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, TFuncGet mFuncGet, TFuncSet mFuncSet)
					: ItemBase{mMenu, mCategory, mName}, predicate{[=]{ return mFuncGet(); }}, activateAction{[=]{ mFuncSet(true); }}, deactivateAction{[=]{ mFuncSet(false); }} { }

				Toggle(Menu& mMenu, Category& mCategory, const std::string& mName, bool& mBool) : ItemBase{mMenu, mCategory, mName},
					predicate{[this, &mBool]{ return mBool; }}, activateAction{[this, &mBool]{ mBool = true; }}, deactivateAction{[this, &mBool]{ mBool = false; }} { }

				inline void exec() override { predicate() ? deactivateAction() : activateAction(); }
				inline std::string getName() const override { return predicate() ? name + ": on" : name + ": off"; }
		};
	}
}

#endif
