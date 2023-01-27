#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>

namespace abyss::Actor::Item
{
    class LifeSpan :
        public IComponent,
        public IUpdate
    {
    public:
        LifeSpan(ActorObj* pActor);
        void onUpdate() override;

        void setLifeSpan(double timeSec)
        {
            m_restTimeSec = timeSec;
        }

        double restTimeSec() const
        {
            return m_restTimeSec;
        }
        bool isWarn() const
        {
            return m_restTimeSec <= 3.0;
        }
    private:
        ActorObj* m_pActor;
        double m_restTimeSec = 0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Item::LifeSpan>
    {
        using Base = Actor::IUpdate;
    };
}