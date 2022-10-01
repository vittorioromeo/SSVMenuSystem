// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_MENUCONTROLLER
#define SSVMS_MENUCONTROLLER

#include "SSVMenuSystem/Global/Typedefs.hpp"

#include <vector>

namespace ssvms
{
    namespace Impl
    {
        class Controller
        {
        private:
            struct Pair
            {
                ItemBase* fst;
                Predicate snd;
            };

            std::vector<Pair> enableWhenPairs;

        public:
            inline void enableItemWhen(ItemBase& mItem, Predicate mPred)
            {
                enableWhenPairs.push_back(Pair{&mItem, mPred});
            }
            inline void update()
            {
                for(const auto& p : enableWhenPairs)
                    p.fst->setEnabled(p.snd());
            }
        };
    }
}

#endif
