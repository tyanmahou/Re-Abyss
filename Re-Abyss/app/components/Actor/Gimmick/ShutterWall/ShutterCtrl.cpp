#include <abyss/components/Actor/Gimmick/ShutterWall/ShutterCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

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
}
