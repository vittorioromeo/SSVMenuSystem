// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_CATEGORY
#define SSVMS_CATEGORY

#include <vector>
#include <string>
#include <SSVUtils/SSVUtils.h>

namespace ssvms
{
	class Menu;
	class ItemBase;

	namespace Items
	{
		class Toggle;
		class Slider;
	}

	template<typename TCategory, typename T> struct CHelper
	{
		template<typename... TArgs> inline static T* create(Menu& mMenu, TCategory& mCategory, const std::string& mName, TArgs&&... mArgs)
		{
			return new T(mMenu, mCategory, mName, std::forward<TArgs>(mArgs)...);
		}
	};

	template<typename TCategory> struct CHelper<TCategory, Items::Toggle>
	{
		template<typename TFuncGet, typename TFuncSet> inline static Items::Toggle* create(Menu& mMenu, TCategory& mCategory, const std::string& mName, TFuncGet mFuncGet, TFuncSet mFuncSet)
		{
			return new Items::Toggle(mMenu, mCategory, mName, [=]{ return mFuncGet(); }, [=]{ mFuncSet(true); }, [=]{ mFuncSet(false); });
		}
		template<typename... TArgs> inline static Items::Toggle* create(Menu& mMenu, TCategory& mCategory, const std::string& mName, TArgs&&... mArgs)
		{
			return new Items::Toggle(mMenu, mCategory, mName, std::forward<TArgs>(mArgs)...);
		}
	};

	template<typename TCategory> struct CHelper<TCategory, Items::Slider>
	{
		template<typename T, typename TFuncGet, typename TFuncSet> inline static Items::Slider* create(Menu& mMenu, TCategory& mCategory, const std::string& mName, TFuncGet mFuncGet, TFuncSet mFuncSet, T mMin, T mMax, T mIncrement)
		{
			return new Items::Slider(mMenu, mCategory, mName, [=]{ return ssvu::toStr(mFuncGet()); }, [=]{ mFuncSet(ssvu::getClamped(mFuncGet() + mIncrement, mMin, mMax)); }, [=]{ mFuncSet(ssvu::getClamped(mFuncGet() - mIncrement, mMin, mMax)); });
		}
		template<typename... TArgs> inline static Items::Slider* create(Menu& mMenu, TCategory& mCategory, const std::string& mName, TArgs&&... mArgs)
		{
			return new Items::Slider(mMenu, mCategory, mName, std::forward<TArgs>(mArgs)...);
		}
	};

	class Category
	{
		friend class Menu;

		private:
			Menu& menu;
			std::string name;
			std::vector<std::unique_ptr<ItemBase>> items;
			int index{0};

			inline void wrapIndex()
			{
				if(index > static_cast<int>(items.size() - 1)) index = 0;
				else if(index < 0) index = items.size() - 1;
			}

		public:
			Category(Menu& mMenu, const std::string& mName) : menu(mMenu), name{mName} { }

			template<typename T, typename... TArgs> inline T& create(const std::string& mName, TArgs&&... mArgs)
			{
				T* result{CHelper<Category, T>::create(menu, *this, mName, std::forward<TArgs>(mArgs)...)};
				items.push_back(std::unique_ptr<T>(result));
				return *result;
			}

			inline void next()		{ ++index; wrapIndex(); }
			inline void previous()	{ --index; wrapIndex(); }

			inline const std::string& getName()	const								{ return name; }
			inline ItemBase& getItem() const										{ return *(items[index]); }
			inline const std::vector<std::unique_ptr<ItemBase>>& getItems() const	{ return items; }
			inline int getIndex()													{ return index; }
	};
}

#endif
