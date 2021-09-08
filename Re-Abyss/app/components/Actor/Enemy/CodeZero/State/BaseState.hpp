#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BaseState : public IState
    {
    protected:
        HP* m_hp;
        BehaviorCtrl* m_behavior;
        PartsCtrl* m_parts;
    public:
        BaseState();
        void onCache()override;

        void update() override;
    };
}