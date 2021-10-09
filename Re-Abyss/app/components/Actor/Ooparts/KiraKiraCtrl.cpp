#include "KiraKiraCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>
#include "..\..\UI\SaveSelect\Panel\KiraKiraCtrl.hpp"

namespace abyss::Actor::Ooparts
{
    KiraKiraCtrl::KiraKiraCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_algo(pActor->getModule<Effects>(), DrawLayer::WorldBack)
    {}
    void KiraKiraCtrl::setup(Executer executer)
    {
        executer.on<IPreDraw>().addAfter<PursuitCtrl>();
    }
    void KiraKiraCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    void KiraKiraCtrl::onPreDraw()
    {
        m_algo.update(m_body->getPos(), m_pActor->deltaTime());
    }
}
