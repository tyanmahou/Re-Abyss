#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeActor;
    class SenserActor;

    class SenserCtrlModel : public IComponent
    {
        SlimeActor* m_pActor;
        Ref<SenserActor> m_senser;
    public:
        SenserCtrlModel(SlimeActor* pActor);
        void onStart() override;

        void destroy();
    };
}