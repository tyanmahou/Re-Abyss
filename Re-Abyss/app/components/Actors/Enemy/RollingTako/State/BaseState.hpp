#pragma once
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>

#include <abyss/views/Actors/Enemy/RollingTako/RollingTakoVM.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapCollider* m_mapCol;
        ViewCtrl<RollingTakoVM>* m_view;
    public:
        void setup()override;

        void lastUpdate() override;
    };
}
