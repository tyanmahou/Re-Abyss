#pragma once
#include <abyss/components/Common/VModelBase.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>

namespace abyss::Actor
{
    class VModelUpdater:
        public IComponent,
        public IPreDraw
    {
    public:
        VModelUpdater(ActorObj* pActor);

        void setTimeScale(double timeScale)
        {
            m_timeScale = timeScale;
        }
        void onPreDraw() override;

        void setTime(double time)
        {
            m_time = time;
        }
        double getTime() const
        {
            return m_time;
        }
    private:
        ActorObj* m_pActor;
        double m_time{};

        double m_timeScale{ 1.0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::VModelUpdater>
    {
        using Base = Actor::IPreDraw;
    };
}