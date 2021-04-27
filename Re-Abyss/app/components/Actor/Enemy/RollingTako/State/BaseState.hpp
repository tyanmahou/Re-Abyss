#pragma once
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>

#include <abyss/views/Actor/Enemy/RollingTako/RollingTakoVM.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class BaseState : public IState
    {
    protected:
        Body* m_body;
        MapCollider* m_mapCol;
        ViewCtrl<RollingTakoVM>* m_view;
    public:
        void setup()override;

        void lastUpdate() override;
    };
}
