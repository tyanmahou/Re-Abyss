#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>

namespace abyss::Actor::CodeZero::Hand
{
    class KindModel : public IComponent
    {

    private:
        HandActor::Kind m_kind;
    public:
        KindModel(HandActor::Kind kind):
            m_kind(kind)
        {}

        HandActor::Kind getKind() const { return m_kind; }
        bool isLeftHand() const { return m_kind == HandActor::Kind::Left; }
        bool isRightHand() const { return m_kind == HandActor::Kind::Right; }
    };
}