#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class ParentCtrlModel;
}
namespace abyss::Actor::Enemy::CodeZero::Head
{
    class DamageModel :
        public IComponent,
        public ICollisionCallbackModel
    {
    protected:
        Ref<ParentCtrlModel> m_parent;
        IActor* m_pActor;
    public:
        DamageModel(IActor* pActor);

        void setup() override;
        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::CodeZero::Head::DamageModel>
    {
        using Base = ICollisionCallbackModel;
    };
}