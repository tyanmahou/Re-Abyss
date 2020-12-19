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
        IActor* m_pActor;
        Ref<IActor> m_senser;
    public:
        SenserCtrl(IActor* pActor);
        void onStart() override;

        void destroy();
    };
}