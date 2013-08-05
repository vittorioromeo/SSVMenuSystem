// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENUCONTROLLER
#define SSVMS_MENUCONTROLLER

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "SSVMenuSystem/Menu/ItemBase.h"
#include "SSVMenuSystem/Menu/Category.h"

namespace ssvms
{
	class MenuController
	{
		public:
			using Predicate = std::function<bool()>;

		private:
			std::vector<std::pair<ItemBase&, Predicate>> enableIfPairs;

		public:
			inline void enableItemIf(ItemBase& mItem, Predicate mPred) { enableIfPairs.emplace_back(mItem, mPred); }
			inline void update() { for(const auto& p : enableIfPairs) p.first.setEnabled(p.second()); }
	};
}

#endif
