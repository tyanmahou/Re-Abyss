#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss::Enemy
{
    class DeadCallbackModel :
        public IComponent,
        public IDeadCallbackModel
    {
    protected:
        EnemyActor* m_pActor;
    public:
        DeadCallbackModel(EnemyActor* pActor);

        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Enemy::DeadCallbackModel>
    {
        using Base = IDeadCallbackModel;
    };
}