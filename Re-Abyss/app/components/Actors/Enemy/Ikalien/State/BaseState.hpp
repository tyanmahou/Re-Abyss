#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
        ViewCtrl<IkalienVM>* m_view;
    public:
        void setup()override;
    };
}
