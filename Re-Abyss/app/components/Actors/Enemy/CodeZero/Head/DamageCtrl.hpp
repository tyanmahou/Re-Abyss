#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrl;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class DamageCtrl :
        public IComponent,
        public ICollisionCallbackModel
    {
    protected:
        Ref<ParentCtrl> m_parent;
        IActor* m_pActor;
    public:
        DamageCtrl(IActor* pActor);

        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Head::DamageCtrl>
    {
        using Base = ICollisionCallbackModel;
    };
}