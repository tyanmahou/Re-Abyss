#include <abyss/components/Actor/Gimmick/ShutterWall/MainCollider.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    MainCollider::MainCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void MainCollider::onStart()
    {
        m_shutter = m_pActor->find<ShutterCtrl>();
    }
    CShape MainCollider::getCollider() const
    {
        return m_shutter->getRegion();
    }
}
