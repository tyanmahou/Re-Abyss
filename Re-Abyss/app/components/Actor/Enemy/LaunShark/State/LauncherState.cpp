#include <abyss/components/Actor/Enemy/LaunShark/State/LauncherState.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/State/SwimState.hpp>

#include <Siv3D.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>

#include <abyss/components/Actor/Enemy/LaunShark/Shot/Builder.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    LauncherState::LauncherState():
        m_attackTimer(Param::Launcher::AttackTimeSec),
        m_waitTimer(Param::Launcher::WaitTimeSec)
    {}
    void LauncherState::start()
    {
        m_motion->set(Motion::Launcher)
            .setAnimeTime(0.0);

        m_body->setAccelX(0);
        m_body->setVelocityY(0);

        m_pActor->find<BodyUpdater>()->setActive(false);
    }
    void LauncherState::update()
    {
        double dt = m_pActor->deltaTime();
        m_attackTimer.update(dt);
        if (m_attackTimer.isEnd()) {
            if (!m_out) {
                if (!m_waitTimer.isRunning()) {
                    int32 page = static_cast<int32>(Periodic::Square0_1(Param::View::SwimAnimeTimeSec, this->m_pActor->getTimeSec()));
                    double offsetY = page == 1 ? 8 : 4;
                    Vec2 shotPos = m_body->getPos() + (m_body->isForward(Forward::Left()) ? Vec2{ -62, offsetY } : Vec2{ 62, offsetY });
                    m_pActor->getModule<Actors>()->create<Shot::Builder>(shotPos, m_body->getForward());
                }
                m_waitTimer.update(dt);
                if (m_waitTimer.isEnd()) {
                    m_attackTimer.reset();
                    m_out = true;
                }
            } else {
                this->changeState<SwimState>();
            }
        }
        m_motion
            ->setAnimeTime(m_out ? m_attackTimer.invRate() : m_attackTimer.rate());
    }
    void LauncherState::end()
    {
        m_pActor->find<BodyUpdater>()->setActive(true);
    }
}
