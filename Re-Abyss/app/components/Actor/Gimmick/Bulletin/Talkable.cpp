#include "Talkable.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/UI/SpeechBalloon/Builder.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Event/Talk/Builder.hpp>

#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    Talkable::Talkable(ActorObj* pActor, const s3d::String& eventPath):
        m_pActor(pActor),
        m_eventPath(eventPath)
    {}

    void Talkable::onStart()
    {
        m_balloon = m_pActor
            ->getModule<UIs>()
            ->create<UI::SpeechBalloon::Builder>(m_pActor);
        m_balloon->setActive(false);

        m_collider = m_pActor->find<Collider>()->main();
    }

    void Talkable::onEnd()
    {
        if (m_balloon) {
            m_balloon->destroy();
        }
    }

    void Talkable::onGimmickReact(ActorObj * player)
    {
        bool isChecked = [&] {
            if (m_event) {
                return false;
            }
            if (!m_pActor->getModule<Events>()->isEmpty()) {
                return false;
            }
            if (!m_collider) {
                return false;
            }
            auto playerCollider = player->find<Collider>()->main();
            if (!playerCollider) {
                return false;
            }
            if (!ColisionUtil::Intersects(playerCollider->getCollider(), m_collider->getCollider())) {
                return false;
            }
            return true;
        }();
        m_balloon->setActive(isChecked);

        if (!isChecked) {
            return;
        }

        if (InputManager::Up.down()) {
            m_event = m_pActor->getModule<Events>()
                ->create<Event::Talk::Builder>(m_eventPath, m_pActor->find<ILocator>());
            m_balloon->setActive(false);
        }
    }
}
