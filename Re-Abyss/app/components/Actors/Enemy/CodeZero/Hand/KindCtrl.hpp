#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class KindCtrl : public IComponent
    {

    private:
        HandActor::Kind m_kind;
    public:
        KindCtrl(HandActor::Kind kind):
            m_kind(kind)
        {}

        HandActor::Kind getKind() const { return m_kind; }
        bool isLeftHand() const { return m_kind == HandActor::Kind::Left; }
        bool isRightHand() const { return m_kind == HandActor::Kind::Right; }
    };
}