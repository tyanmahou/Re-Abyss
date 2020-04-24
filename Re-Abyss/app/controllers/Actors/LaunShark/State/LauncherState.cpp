#include "LauncherState.hpp"

#include <Siv3D.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/LaunShark/LaunSharkVM.hpp>

#include <abyss/controllers/Actors/LaunShark/Shot/ShotActor.hpp>
#include <abyss/params/Actors/LaunShark/Param.hpp>

namespace abyss::LaunShark
{
    LauncherState::LauncherState():
        m_attackTimer(Param::Launcher::AttackTimeSec, true, WorldTime::TimeMicroSec),
        m_waitTimer(Param::Launcher::WaitTimeSec, false, WorldTime::TimeMicroSec)
    {}
    void LauncherState::start()
    {
        m_body->setAccelX(0);
        m_body->setVelocityY(0);
    }
    void LauncherState::update([[maybe_unused]]double dt)
    {
        if (m_attackTimer.reachedZero()) {
            if (!m_out) {
                if (!m_waitTimer.isRunning()) {
                    m_waitTimer.start();
                    int32 page = static_cast<int32>(Periodic::Square0_1(Param::View::SwimAnimeTimeSec, WorldTime::Time()));
                    double offsetY = page == 1 ? 8 : 4;
                    Vec2 shotPos = m_body->getPos() + (m_body->isForward(Forward::Left) ? Vec2{ -62, offsetY } : Vec2{ 62, offsetY });
                    m_actor->getModule<World>()->create<Shot::ShotActor>(shotPos, m_body->getForward());
                }
                if (m_waitTimer.reachedZero()) {
                    m_attackTimer.restart();
                    m_out = true;
                }
            } else {
                this->changeState(LaunSharkActor::State::Swim);
            }
        }
    
    }
    void LauncherState::draw() const
    {
        double t = m_out ? m_attackTimer.progress1_0() : m_attackTimer.progress0_1();
        this->m_actor->getBindedView()->drawLauncher(t);
    }
}
