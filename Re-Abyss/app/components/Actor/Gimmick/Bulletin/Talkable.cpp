#include "Talkable.hpp"
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/UI/SpeechBalloon/Builder.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    Talkable::Talkable(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void Talkable::onStart()
    {
        m_balloon = m_pActor
            ->getModule<UIs>()
            ->create<UI::SpeechBalloon::Builder>(m_pActor);
    }

    void Talkable::onEnd()
    {
        if (m_balloon) {
            m_balloon->destroy();
        }
    }

    void Talkable::onGimmickReact(ActorObj * player)
    {}
}
