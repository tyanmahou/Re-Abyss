#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss::Actor::Enemy
{
    class DeadCallbackModel :
        public IComponent,
        public IDeadCallbackModel
    {
    protected:
        IActor* m_pActor;
        bool m_useQuake = true;
    public:
        DeadCallbackModel(IActor* pActor);

        void onDead() override;

        void setUseQuake(bool useQuake)
        {
            m_useQuake = useQuake;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::DeadCallbackModel>
    {
        using Base = IDeadCallbackModel;
    };
}