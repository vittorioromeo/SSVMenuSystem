// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_BIND
#define SSVMS_ITEM_BIND

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
		class BindControl final : public ItemBase
		{
		private:
            using GameState = ssvs::GameState;
#ifdef OPEN_HEXAGON
            using HexagonGame = hg::HexagonGame;
#endif
			using Combo = ssvs::Input::Combo;
			using KKey = ssvs::KKey;
			using MBtn = ssvs::MBtn;
            using Tid = ssvs::Input::Tid;
            using Trigger = ssvs::Input::Trigger;
			using TriggerGetter = std::function<Trigger()>;
            using SizeGetter = std::function<int()>;
            
            TriggerGetter triggerGetter;
            SizeGetter sizeGetter;
			Action getBind, addBind, clearBind;
            GameState& game;
#ifdef OPEN_HEXAGON
            HexagonGame& hexagonGame;
#endif
            Tid triggerID;
            
            bool waitingForBind{false};
            KKey setKey{KKey::Unknown};
            MBtn setBtn{MBtn::Left};
            
            inline int getRealSize(const std::vector<Combo> combos) const
            {
                int i, size = combos.size();
                for (i = 0; i < size; ++i)
                    if(combos[i].isUnbound()) break;
                return i;
            }

		public:
			template <typename TFuncGet, typename TFuncSet, typename TFuncClear>
			BindControl(Menu& mMenu, Category& mCategory, const std::string& mName,
						TFuncGet mFuncGet, TFuncSet mFuncSet, TFuncClear mFuncClear,
                        GameState& mGame,
#ifdef OPEN_HEXAGON
						HexagonGame& mHexagonGame,
#endif
						Tid mtriggerID)
				: ItemBase{mMenu, mCategory, mName},
                  triggerGetter{[=, this] { return mFuncGet(); }},
                  sizeGetter{[=, this] { return getRealSize(triggerGetter().getCombos()); }},
				  getBind{[=] { mFuncGet(); }},
				  addBind{[=, this] { mFuncSet(setKey, setBtn, sizeGetter()); }},
                  clearBind{[=, this] { mFuncClear(sizeGetter()); }},
                  game{mGame},
#ifdef OPEN_HEXAGON
                  hexagonGame{mHexagonGame},
#endif
                  triggerID{mtriggerID}
			{
			}
            
            inline void exec() override //if bind spots are full do not allow binding
            {
                if(!waitingForBind)
                    waitingForBind = sizeGetter() < 2;
                else
                    waitingForBind = false;
            }
            inline bool isWaitingForBind() override { return waitingForBind; }
			inline bool erase() override
            {
                const int size = sizeGetter();
                if(!size) return false;
                
                clearBind();
                game.refreshTrigger(triggerGetter(), triggerID);
#ifdef OPEN_HEXAGON
                hexagonGame.refreshTrigger(triggerGetter(), triggerID);
#endif
                return true;
            }
            
            inline bool newBind(const KKey key, const MBtn btn) override
            {
                const std::vector<Combo> combos = triggerGetter().getCombos();
                
                //check if the desired key/btn has already been assigned
#ifdef OPEN_HEXAGON
                if(game.isBindAssigned(key, btn) || hexagonGame.isBindAssigned(key, btn))
#else
				if(game.isBindAssigned(key, btn))
#endif
                    return false;

                setKey = key;
                setBtn = btn;
                addBind();
                
                game.refreshTrigger(triggerGetter(), triggerID);
#ifdef OPEN_HEXAGON
                hexagonGame.refreshTrigger(triggerGetter(), triggerID);
#endif
                
                setKey = KKey::Unknown;
                setBtn = MBtn::Left;
                waitingForBind = false;
                return true;
            }

			inline std::string getName() const override
			{
				const std::vector<Combo> combos = triggerGetter().getCombos();
                const int size = sizeGetter();
				std::string bindNames;
                std::bitset<102> keyBind;
                std::bitset<6> btnBinds;
				int i, j;

                //get binds in the order they have been entered
				for(i = 0; i < size; ++i)
                {
                    keyBind = combos[i].getKeys();
					for(j = 0; j <= KKey::KeyCount; ++j) //FXX keys and upwards are not considered
					{
						if(keyBind[j])
                        {
                            if(!bindNames.empty()) bindNames += ", ";
                            bindNames += ssvs::getKKeyName(KKey(j - 1)); //names are shifted compared to the Key enum
                            break;
                        }
					}

                    btnBinds = combos[i].getBtns();
                    for(j = 0; j <= MBtn::ButtonCount; ++j)
                    {
                        if(btnBinds[j])
                        {
                            if(!bindNames.empty()) bindNames += ", ";
                            bindNames += ssvs::getMBtnName(MBtn(j - 1)); //same as with keys
                            break;
                        }
                    }
				}

                if(waitingForBind)
                    bindNames += "_";
				
				return name + ": " + bindNames;
			}
		};
	}
}

#endif
