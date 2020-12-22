#include "Main.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>

#include <abyss/debugs/Log/Log.hpp>

namespace abyss::ui::PlayerInfo
{
    Main::Main(IUserInterface* pUi, Actor::IActor* pActor):
        m_pUi(pUi),
        m_pActor(pActor)
    {}

    void Main::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
    }

    void Main::onUpdate()
    {
    }

    void Main::onDraw() const
    {
#if ABYSS_DEBUG
        Debug::Log::Print << m_hpModel->getHp() << U"/" << m_hpModel->getMaxHp();
#endif
    }

}
