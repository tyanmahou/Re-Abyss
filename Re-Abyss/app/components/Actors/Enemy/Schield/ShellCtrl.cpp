#include "ShellCtrl.hpp"
#include <abyss/controllers/World/World.hpp>
#include <abyss/components/Actors/Enemy/Schield/Shell/Builder.hpp>

namespace abyss::Actor::Enemy::Schield
{
    ShellCtrl::ShellCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    ShellCtrl::~ShellCtrl()
    {
        if (m_shell) {
            m_shell->destroy();
        }
    }
    void ShellCtrl::onStart()
    {
        m_shell = m_pActor->getModule<World>()->create<Shell::Builder>(m_pActor);
    }
    void ShellCtrl::onDead()
    {
        if (m_shell) {
            m_shell->destroy();
            m_shell = nullptr;
        }
    }
}

