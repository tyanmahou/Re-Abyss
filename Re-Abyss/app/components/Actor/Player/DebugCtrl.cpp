#include <abyss/components/Actor/Player/DebugCtrl.hpp>
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
namespace abyss::Actor::Player
{
    DebugCtrl::DebugCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrl::onUpdate()
    {
        auto dt = m_pActor->deltaTime();

        auto hp = m_pActor->find<HP>();
        if ((KeyShift + KeyD).down()) {
            hp->setHp(1);
        } else if (KeyD.down()) {
            hp->setHp(0);
        } else if (KeyS.down()) {
            hp->reset();
        }

        auto* camera = m_pActor->getModule<Camera>();
        if ((KeyQ + KeyW).down()) {
            camera->setZoomScale(1.0);
        } else if (KeyQ.pressed() && KeyQ.pressedDuration() >= 1s) {
            camera->setZoomScale(camera->getZoomScale() + dt);
        } else if (KeyW.pressed() && KeyW.pressedDuration() >= 1s) {
            camera->setZoomScale(s3d::Max(0.0, camera->getZoomScale() - dt));
        }
    }

}
#endif