#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/TimeCounter.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/views/Actor/Enemy/LaunShark/LaunSharkVM.hpp>

namespace abyss::Actor::Enemy::LaunShark
{
    class BaseState : public IState
    {
    protected:
        Body* m_body;
        MapCollider* m_mapCol;
        TimeCounter* m_timeCounter;
        ViewCtrl<LaunSharkVM>* m_view;
    public:
        void update() override;
        void setup()override;

        void lastUpdate() override;
    };
}
