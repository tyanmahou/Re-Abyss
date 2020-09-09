#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/RotateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        RotateCtrl* m_rotate;
        ViewCtrl<IkalienVM>* m_view;
    public:
        void setup()override;
    };
}
