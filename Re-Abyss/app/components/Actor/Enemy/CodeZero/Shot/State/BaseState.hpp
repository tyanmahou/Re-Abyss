#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ScaleCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        Body* m_body;
        ScaleCtrl* m_scale;
    public:
        void onCache() override;

        void lastUpdate() override;
    };
}