#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>

#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>

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