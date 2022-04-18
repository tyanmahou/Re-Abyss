#include <abyss/components/Actor/Enemy/CodeZero/DeadCallback.hpp>

#include <abyss/commons/Path.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>
#include <abyss/components/Event/Talk/Builder.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    DeadCallback::DeadCallback(ActorObj* pActor) :
        m_pActor(pActor)
    {}

    void DeadCallback::setDeadEventPath(const s3d::String & path)
    {
        m_deadEventPath = path;
    }

    void DeadCallback::onDead()
    {
        if (m_deadEventPath) {
            m_pActor->getModule<Events>()->create<Event::Talk::Builder>(Path::NovelPath + * m_deadEventPath);
        }
        DeadState::Change(m_pActor);
    }
}