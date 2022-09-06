#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterUtil.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    ShutterCtrl::ShutterCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
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
        // 最新地形サイズ更新
        const Vec2& pos = m_terrain->tl();
        m_terrain->setRegion(ShutterUtil::Region(pos, m_shutterRate));
    }
}
