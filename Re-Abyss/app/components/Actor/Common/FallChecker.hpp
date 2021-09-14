#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>

namespace abyss::Actor
{
    class FallChecker :
        public IComponent,
        public ILastUpdate
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<DeadChecker> m_deadChecker;
        Ref<Body> m_body;

        bool m_isFall = false;
    public:
        FallChecker(ActorObj* pActor);

        void onStart() override;
        void onLastUpdate() override;

        bool isFall() const
        {
            return m_isFall;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::FallChecker>
    {
        using Base = Actor::ILastUpdate;
    };
}