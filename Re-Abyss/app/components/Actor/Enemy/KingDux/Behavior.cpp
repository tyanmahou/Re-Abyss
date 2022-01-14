#include "Behavior.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/StabState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/PursuitStabState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <Siv3D.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Devs/WorldComment/WorldComment.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    Coro::Task<> Behavior::Test(ActorObj* pActor)
    {
        Array<std::pair<String, std::function<Coro::Task<>(ActorObj*)>>> commands;
        commands.emplace_back(U"Stab", Stab);
        commands.emplace_back(U"Stab2", Stab2);
        commands.emplace_back(U"Stab3", Stab3);
        commands.emplace_back(U"PursuitStab", PursuitStab);
        commands.emplace_back(U"Convene", Convene);
        size_t select = 0;
        auto worldComment = pActor->getModule<WorldComment>()->getRequestor();
        auto body = pActor->find<Body>();
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};

        while (!commands.empty()) {
            pActor->find<StateCtrl>()->changeState<WaitState>();
            co_yield{};

            // 技選択
            while (true) {
                if (worldComment->isSelected()) {
                    String text = U"◀ {} ▶"_fmt(commands[select].first);
                    worldComment->comment(text, body->region().topCenter(), ColorF(0.8, 1.0, 1.0, 0.8));

                    if (InputManager::A.down()) {
                        break;
                    }
                    if (InputManager::Left.down()) {
                        if (select == 0) {
                            select = commands.size() - 1;
                        } else {
                            --select;
                        }
                    } else if (InputManager::Right.down()) {
                        if (select == commands.size() - 1) {
                            select = 0;
                        } else {
                            ++select;
                        }
                    }
                } else {
                    worldComment->comment(U"...", body->region().topCenter(), ColorF(0.8, 1.0, 1.0, 0.8));
                }
                co_yield{};
            }
            co_await commands[select].second(pActor);
        }
        co_return;
    }
    Coro::Task<> Behavior::Petern(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};

        co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);

        while (true) {
            // 突き
            co_await Stab(pActor);

            co_await Stab2(pActor);

            co_await Stab3(pActor);

            co_await PursuitStab(pActor);
        }
        co_return;
    }
    Coro::Task<> Behavior::Stab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle);
        co_yield{};
    }
    Coro::Task<> Behavior::Stab2(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle2);
        co_yield{};
    }
    Coro::Task<> Behavior::Stab3(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle3);
        co_yield{};
    }
    Coro::Task<> Behavior::PursuitStab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<PursuitStabState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Convene(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>();
        co_yield{};
    }
}
