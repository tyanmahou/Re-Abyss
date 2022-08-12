#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class TargetCtrl final :
        public IComponent
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
    private:
        ActorObj* m_pActor = nullptr;
        bool m_isMirrored;
        bool m_isFlipped;
        double m_rotate;
    };
}
