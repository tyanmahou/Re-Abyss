#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::Slime
{
    class SlimeActor;
    class SenserActor;

    class SenserCtrl : public IComponent
    {
        ActorObj* m_pActor;
        Ref<ActorObj> m_senser;
    public:
        SenserCtrl(ActorObj* pActor);
        void onStart() override;

        void destroy();
    };
}