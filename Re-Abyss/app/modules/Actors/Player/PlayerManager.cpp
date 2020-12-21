#include "PlayerManager.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor::Player
{
    void PlayerManager::regist(const Ref<IActor>& player)
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
    const Ref<IActor>& PlayerManager::getActor() const
    {
        return m_player;
    }
}

