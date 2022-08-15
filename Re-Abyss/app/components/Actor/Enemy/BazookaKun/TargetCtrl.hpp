#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class TargetCtrl final :
        public IComponent,
        public ILastUpdate
    {
    public:
        TargetCtrl(ActorObj* pActor);

        TargetCtrl& setIsMirrored(bool isMirrored)
        {
            m_isMirrored = isMirrored;
            return *this;
        }
        bool isMirrored() const
        {
            return m_isMirrored;
        }
        TargetCtrl& setIsFlipped(bool isFlipped)
        {
            m_isFlipped = isFlipped;
            return *this;
        }
        bool isFlipped() const
        {
            return m_isFlipped;
        }
        TargetCtrl& setRotate(double rotate)
        {
            m_rotate = rotate;
            return *this;
        }
        double rotate() const
        {
            return m_rotate;
        }

        double bazookaRotate() const
        {
            return m_bazookaRotate;
        }
    public:
        void onStart() override;

        void onLastUpdate() override;
    private:
        ActorObj* m_pActor = nullptr;
        bool m_isMirrored = false;
        bool m_isFlipped = false;
        double m_rotate = 0;

        double m_bazookaRotate = 0;
        double m_bazookaRotateTarget = 0;

        TimeLite::Timer m_waitTimer;

        Ref<Body> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::BazookaKun::TargetCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate
        >;
    };
}
