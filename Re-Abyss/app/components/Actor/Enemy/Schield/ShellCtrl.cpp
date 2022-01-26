#include <abyss/components/Actor/Enemy/Schield/ShellCtrl.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Enemy/Schield/Shell/Builder.hpp>

namespace abyss::Actor::Enemy::Schield
{
    ShellCtrl::ShellCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    ShellCtrl::~ShellCtrl()
    {
    }
    void ShellCtrl::onStart()
    {
        m_shell = m_pActor->getModule<World>()->create<Shell::Builder>(m_pActor);
    }
    void ShellCtrl::onEnd()
    {
        if (m_shell) {
            m_shell->destroy();
        }
    }
    void ShellCtrl::onDead()
    {
        if (m_shell) {
            m_shell->destroy();
            m_shell = nullptr;
        }
    }
}

