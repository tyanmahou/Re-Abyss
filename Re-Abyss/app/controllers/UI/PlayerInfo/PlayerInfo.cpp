#include "PlayerInfo.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace abyss::ui
{
    PlayerInfo::PlayerInfo(Actor::IActor* actor):
        m_pActor(actor)
    {}

    void PlayerInfo::start()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
    }

    void PlayerInfo::update([[maybe_unused]]double dt)
    {
    }

    void PlayerInfo::draw() const
    {
#if ABYSS_DEBUG
        Debug::Log::Print << m_hpModel->getHp() << U"/" << m_hpModel->getMaxHp();
#endif
    }
}
