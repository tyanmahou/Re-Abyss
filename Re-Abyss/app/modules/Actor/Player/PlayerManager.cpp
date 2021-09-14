#include "PlayerManager.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Player
{
    void PlayerManager::regist(const Ref<ActorObj>& player)
    {
        m_player = player;
        m_body = player->find<Body>();
    }
    PlayerManager& PlayerManager::setPos(const s3d::Vec2& pos)
    {
        m_body->setPos(pos);
        return *this;
    }
    const s3d::Vec2& PlayerManager::getPos() const
    {
        return m_body->getPos();
    }
    const Ref<ActorObj>& PlayerManager::getActor() const
    {
        return m_player;
    }
}

