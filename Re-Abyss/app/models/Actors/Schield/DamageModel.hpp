#pragma once
#include <abyss/models/Actors/Commons/DamageModel.hpp>
#include <abyss/controllers/Actors/Schield/SchieldActor.hpp>
namespace abyss::Schield
{
    class DamageModel :
        public abyss::DamageModel
    {
        Ref<StateModel<SchieldActor>> m_state;
    public:
        DamageModel(IActor* pActor);

        void setup() override;

        void onCollisionStay(IActor* col)override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Schield::DamageModel>
    {
        using Base = abyss::DamageModel;
    };
}