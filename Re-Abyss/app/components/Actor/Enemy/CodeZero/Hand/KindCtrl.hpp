#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    enum class HandKind
    {
        Left,
        Right
    };
    class KindCtrl : public IComponent
    {
    private:
        HandKind m_kind;
    public:
        KindCtrl(HandKind kind):
            m_kind(kind)
        {}

        HandKind getKind() const { return m_kind; }
        bool isLeftHand() const { return m_kind == HandKind::Left; }
        bool isRightHand() const { return m_kind == HandKind::Right; }
    };
}