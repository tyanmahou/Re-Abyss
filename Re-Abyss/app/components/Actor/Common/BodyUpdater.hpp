#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IMove.hpp>

namespace abyss::Actor
{
    class BodyUpdater :
        public IComponent,
        public IMove
    {
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        bool m_isActive = true;
    public:
        BodyUpdater(ActorObj* pActor);

        void onStart() override;
        void onMove() override;

        BodyUpdater& setActive(bool isActive)
        {
            m_isActive = isActive;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BodyUpdater>
    {
        using Base = Actor::IMove;
    };
}