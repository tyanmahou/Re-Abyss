#include "BossMove.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Demo/DemoActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
namespace abyss::Event::Talk::BossTalk0_0
{
    void BossMove::init()
    {
        auto world = m_pManager->getModule<World>();
        m_codeZero = world->find<CodeZero::Demo::DemoActor>();
        m_initPos = m_codeZero->getPos();

        m_targetPos = m_initPos - s3d::Vec2{ 0, 400 };

        m_pManager->getModule<Camera>()->startQuake(2.0);
    }

    bool BossMove::update(double dt)
    {
        if (!m_codeZero) {
            return false;
        }
        if (m_codeZero->moveToTarget(dt)) {
            return true;
        }
        auto camera = m_pManager->getModule<Camera>();
        if (!m_isRequestedLastQuake) {
            camera->startQuake(10, 0.3);
            m_isRequestedLastQuake = true;
        }
        return camera->isQuake();
    }

    void BossMove::onEnd()
    {
        m_pManager->getModule<Camera>()->stopQuake();
        if (!m_codeZero) {
            return;
        }
        m_codeZero->setPos(m_targetPos);
    }
}
