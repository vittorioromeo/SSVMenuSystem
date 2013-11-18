// Copyright (c) 2013 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENUCONTROLLER
#define SSVMS_MENUCONTROLLER

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "SSVMenuSystem/Menu/ItemBase.hpp"
#include "SSVMenuSystem/Menu/Category.hpp"

namespace ssvms
{
	namespace Internal
	{
		class Controller
		{
			private:
				std::vector<std::pair<ItemBase&, Predicate>> enableWhenPairs;

			public:
				inline void enableItemWhen(ItemBase& mItem, Predicate mPred) { enableWhenPairs.emplace_back(mItem, mPred); }
				inline void update() { for(const auto& p : enableWhenPairs) p.first.setEnabled(p.second()); }
		};
	}
}

#endif
