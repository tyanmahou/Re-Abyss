#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/Components.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor
{
    class BreathingCtrl : 
        public IComponent,
        public ILastUpdate
    {
    public:
        BreathingCtrl(ActorObj* pActor);

        void onStart() override;
        void onLastUpdate() override;

        void setOffset(const Vec2& offset)
        {
            m_offset = offset;
        }
    private:
        ActorObj* m_pActor;
        IntervalTimer m_timer;
        s3d::Vec2 m_offset;
        double m_timeOffsetSec = 0;
        Ref<Body> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::BreathingCtrl>
    {
        using Base = Actor::ILastUpdate;
    };
}