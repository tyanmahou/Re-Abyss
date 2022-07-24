#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::Actor::Player
{
    void PlayerManager::regist(const Ref<ActorObj>& player)
    {
        m_player = player;
        m_body = player->find<Body>();
        m_hp = player->find<HP>();
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
    PlayerDesc PlayerManager::getDesc(bool asDirect) const
    {
        PlayerDesc desc;
        desc.hp = m_hp->getHp();
        if (asDirect) {
            desc.direct = PlayerDesc::DirectInfo{
                .pos = m_body->getPos(),
                .forward = m_body->getForward()
            };
        }
        return desc;
    }
    PlayerDesc PlayerManager::getDescAsDirect() const
    {
        return this->getDesc(true);
    }
}

