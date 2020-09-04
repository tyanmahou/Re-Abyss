#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeActor;
    class SenserActor;

    class SenserCtrl : public IComponent
    {
        SlimeActor* m_pActor;
        Ref<SenserActor> m_senser;
    public:
        SenserCtrl(SlimeActor* pActor);
        void onStart() override;

        void destroy();
    };
}