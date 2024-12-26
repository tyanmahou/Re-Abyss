#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Gimmick/ShutterWall/Param.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterCtrl::ShutterCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_shutterTimer(Param::ShutterTime)
    {
        m_task.reset(std::bind(&ShutterCtrl::anim, this));
    }
    double ShutterCtrl::getShutterRate() const
    {
        return m_shutterTimer.rate();
    }
    Coro::Fiber<> ShutterCtrl::anim()
    {
        while (!m_shutterTimer.isEnd()) {
            co_yield{};
        }
        // 地震
        m_pActor->getModule<Camera>()->startQuake(Param::Quake::Offset, Param::Quake::TimeSec);
        m_col->setActive(true);

        co_return;
    }
    void ShutterCtrl::setup(Executer executer)
    {
        executer.onStart().addAfter<TerrainProxy>();
        executer.onStart().addAfter<ColCtrl>();
    }
    void ShutterCtrl::onStart()
    {
        m_terrain = m_pActor->find<TerrainProxy>();
        m_col = m_pActor->find<ColCtrl>();
        m_col->setActive(false);
    }
    s3d::RectF ShutterCtrl::getRegion() const
    {
        return ShutterUtil::Region(m_terrain->tl(), this->getShutterRate());
    }
    void ShutterCtrl::onPrePhysics()
    {
        const Vec2& pos = m_terrain->tl();

        if (m_isWait) {
            const Vec2& playerPos = ActorUtils::PlayerCenterPos(*m_pActor);
            const Vec2 centerPos = ShutterUtil::CenterPosFromTl(pos);

            auto toPlayer = playerPos - centerPos;
            if (Abs(toPlayer.x) <= Param::ActionRange) {
                m_isWait = false;
            }
        }
        if (!m_isWait) {
            m_shutterTimer.update(m_pActor->deltaTime());
        }
        m_task.resume();

        // 最新地形サイズ更新
        m_terrain->setRegion(ShutterUtil::Region(pos, this->getShutterRate()));
    }
}
