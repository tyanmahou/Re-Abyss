#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/RotateCtrl.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/views/Actor/Enemy/Ikalien/IkalienVM.hpp>

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
