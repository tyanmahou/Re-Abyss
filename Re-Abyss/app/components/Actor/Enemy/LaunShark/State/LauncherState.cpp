#include "LauncherState.hpp"
#include "SwimState.hpp"

#include <Siv3D.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>

#include <abyss/components/Actor/Enemy/LaunShark/Shot/Builder.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    LauncherState::LauncherState()
    {}
    Task<> LauncherState::start()
    {
        m_attackTimer = ActorUtils::CreateTimer(*m_pActor, Param::Launcher::AttackTimeSec);
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Launcher::WaitTimeSec, false);
        m_body->setAccelX(0);
        m_body->setVelocityY(0);

        m_pActor->find<BodyUpdater>()->setActive(false);
        co_return;
    }
    void LauncherState::update()
    {
        if (m_attackTimer.reachedZero()) {
            if (!m_out) {
                if (!m_waitTimer.isRunning()) {
                    m_waitTimer.start();
                    int32 page = static_cast<int32>(Periodic::Square0_1(Param::View::SwimAnimeTimeSec, this->m_pActor->getDrawTimeSec()));
                    double offsetY = page == 1 ? 8 : 4;
                    Vec2 shotPos = m_body->getPos() + (m_body->isForward(Forward::Left) ? Vec2{ -62, offsetY } : Vec2{ 62, offsetY });
                    m_pActor->getModule<World>()->create<Shot::Builder>(shotPos, m_body->getForward());
                }
                if (m_waitTimer.reachedZero()) {
                    m_attackTimer.restart();
                    m_out = true;
                }
            } else {
                this->changeState<SwimState>();
            }
        }
    }
    void LauncherState::end()
    {
        m_pActor->find<BodyUpdater>()->setActive(true);
    }

    void LauncherState::draw()const
    {
        double launcherTime = m_out ? m_attackTimer.progress1_0() : m_attackTimer.progress0_1();
        (*m_view)->drawLauncher(launcherTime);
    }
}
