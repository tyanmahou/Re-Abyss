#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/RotateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class BaseState : public IState
    {
    protected:
        Body* m_body;
        RotateCtrl* m_rotate;
        ViewCtrl<IkalienVM>* m_view;
    public:
        void setup()override;
    };
}
