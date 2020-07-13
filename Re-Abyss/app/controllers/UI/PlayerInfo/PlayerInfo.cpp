#include "PlayerInfo.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace abyss::ui
{
    PlayerInfo::PlayerInfo(IActor* actor):
        m_pActor(actor)
    {}

    void PlayerInfo::start()
    {
        m_hpModel = m_pActor->find<HPModel>();
    }

    void PlayerInfo::update(double dt)
    {
    }

    void PlayerInfo::draw() const
    {
#if ABYSS_DEBUG
        Debug::Log::Print << m_hpModel->getHp() << L"/" << m_hpModel->getMaxHp();
#endif
    }
}
