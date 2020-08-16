// Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef SSVMS_ITEM_BIND
#define SSVMS_ITEM_BIND

#include "SSVMenuSystem/Global/Typedefs.hpp"
#include "SSVOpenHexagon/Core/Joystick.hpp"
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
            using BindReturn = std::function<std::tuple<int, Trigger>()>;
            
            TriggerGetter triggerGetter;
            SizeGetter sizeGetter;
            BindReturn addBind;
			Action clearBind;
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
				  addBind{[=, this] { return mFuncSet(setKey, setBtn, sizeGetter()); }},
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
            inline int isWaitingForBind() override { return waitingForBind ? 1 : 0; }
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

            inline void newBind(const KKey key, const MBtn btn, const int joy) override
            {
                (void)(joy);

                // stop if the pressed key is already assigned to this bind
                std::vector Combos = triggerGetter().getCombos();
                int size = sizeGetter();
                if(key > KKey::Unknown)
                {
                    for(int i = 0; i < size; ++i)
                        if(Combos[i].getKeys()[int(key) + 1])
                        {
                            waitingForBind = false;
                            return;
                        }
                }
                else
                {
                    for(int i = 0; i < size; ++i)
                        if(Combos[i].getBtns()[int(btn) + 1])
                        {
                            waitingForBind = false;
                            return;
                        }
                }

                // assign the pressed key to the config value
                setKey = key;
                setBtn = btn;
                auto [unboundID, trig] = addBind();

                // key was assigned to another function and was unbound.
                // This trigger must be refreshed as well
                if(unboundID > -1)
                {
                    game.refreshTrigger(trig, Tid(unboundID));
#ifdef OPEN_HEXAGON
                    hexagonGame.refreshTrigger(trig, Tid(unboundID));
#endif
                }

                // apply the new bind in game
                game.refreshTrigger(triggerGetter(), triggerID);
#ifdef OPEN_HEXAGON
                hexagonGame.refreshTrigger(triggerGetter(), triggerID);
#endif

                // finalize
                waitingForBind = false;
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
					for(j = 0; j <= KKey::KeyCount; ++j)
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


        class JoystickBindControl final : public ItemBase
        {
        private:
            using Jid = hg::Joystick::Jid;
            using ValueGetter = std::function<int()>;

            ValueGetter valueGetter, setButton;
            Jid buttonID;

            bool waitingForBind{false};
            int pressedButton{33};

        public:
            template <typename TFuncGet, typename TFuncSet>
            JoystickBindControl(Menu& mMenu, Category& mCategory, const std::string& mName,
                        TFuncGet mFuncGet, TFuncSet mFuncSet, Jid mButtonID)
                : ItemBase{mMenu, mCategory, mName},
                  valueGetter{[=] { return mFuncGet(); }},
                  setButton{[=, this] { return mFuncSet(pressedButton); }},
                  buttonID{mButtonID}
            {
            }

            inline void exec() override
            {
                waitingForBind = !waitingForBind;
            }
            inline int isWaitingForBind() override { return waitingForBind ? 2 : 0; }
            inline bool erase() override
            {
                if(valueGetter() == 33) return false;

                pressedButton = 33;
                setButton();
                return true;
            }

            inline void newBind(const KKey key, const MBtn btn, const int joy) override
            {
                (void)(key);
                (void)(btn);

                // stop if the pressed button is already assigned to this bind
                if(joy == valueGetter())
                {
                    waitingForBind = false;
                    return;
                }

                // save the new key in config
                pressedButton = joy;
                int unboundID = setButton();

                // if the key was bound to another function and it was reassigned
                // make sure we also update the unbound joystick button
                if(unboundID > -1)
                    hg::Joystick::unbindJoystickButton(unboundID);

                // update the bind we customized
                hg::Joystick::setJoystickBind(joy, buttonID);

                // finalize
                waitingForBind = false;
            }

            inline std::string getName() const override
            {
                std::string bindNames;
                int value = valueGetter();

                if(value == 33)
                    bindNames = "";
                else
                    bindNames = ssvu::toStr(value);

                if(waitingForBind)
                    bindNames += "_";

                return name + ": " + bindNames;
            }
        };
	}
}

#endif
