#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/TimeCounter.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/LaunSharkVM.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapCollider* m_mapCol;
        TimeCounter* m_timeCounter;
        ViewCtrl<LaunSharkVM>* m_view;
    public:
        void update(double dt) override;
        void setup()override;

        void lastUpdate() override;
    };
}
