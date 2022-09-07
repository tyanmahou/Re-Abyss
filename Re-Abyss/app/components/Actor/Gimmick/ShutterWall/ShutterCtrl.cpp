#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterCtrl::ShutterCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_shutterTimer(0.5)
    {}
    double ShutterCtrl::getShutterRate() const
    {
        return m_shutterTimer.rate();
    }
    void ShutterCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<TerrainProxy>();
    }
    void ShutterCtrl::onStart()
    {
        m_terrain = m_pActor->find<TerrainProxy>();
    }
    void ShutterCtrl::onPrePhysics()
    {
        const Vec2& pos = m_terrain->tl();

        if (m_isWait) {
            const Vec2& playerPos = ActorUtils::PlayerPos(*m_pActor);
            const Vec2 centerPos = ShutterUtil::CenterPosFromTl(pos);

            auto toPlayer = playerPos - centerPos;
            if (Abs(toPlayer.x) <= 300) {
                m_isWait = false;
            }
        }
        if (!m_isWait) {
            m_shutterTimer.update(m_pActor->deltaTime());
        }

        // 最新地形サイズ更新
        m_terrain->setRegion(ShutterUtil::Region(pos, this->getShutterRate()));
    }
}
