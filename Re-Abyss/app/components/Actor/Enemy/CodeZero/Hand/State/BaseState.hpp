#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        Body* m_body;
        RotateCtrl* m_rotate;
        HandCtrl* m_hand;
        KindCtrl* m_kind;
        ViewCtrl<HandVM>* m_view;
    public:
        void onCache()override;
        void update() override;
        void draw() const override;
    };
}