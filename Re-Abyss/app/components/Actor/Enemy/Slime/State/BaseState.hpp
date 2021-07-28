#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>

#include <abyss/views/Actor/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Actor::Enemy::Slime
{

    class BaseState : public IState
    {
    protected:
        Body* m_body;
        MapCollider* m_mapCol;
        ViewCtrl<SlimeVM>* m_view;
    public:
        void setup()override;

        void update() override;
        void lastUpdate();
    };
}