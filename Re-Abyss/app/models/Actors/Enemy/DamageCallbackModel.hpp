#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Enemy
{
    class DamageCallbackModel :
        public IComponent,
        public IDamageCallbackModel
    {
    protected:
        IActor* m_pActor;
        Ref<BodyModel> m_body;
    public:
        DamageCallbackModel(IActor* pActor);

        void setup();
        void onDamaged() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Enemy::DamageCallbackModel>
    {
        using Base = IDamageCallbackModel;
    };
}