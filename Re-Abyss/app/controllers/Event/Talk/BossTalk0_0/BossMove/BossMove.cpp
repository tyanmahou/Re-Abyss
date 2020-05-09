#include "BossMove.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/controllers/Actors/CodeZero/Demo/DemoActor.hpp>
namespace abyss::Event::Talk::BossTalk0_0
{
    void BossMove::init()
    {
        auto world = m_pManager->getModule<World>();
        m_codeZero = world->find<CodeZero::Demo::DemoActor>();
        m_initPos = m_codeZero->getPos();

        m_targetPos = m_initPos - s3d::Vec2{ 0, 400 };
    }

    bool BossMove::update(double dt)
    {
        if (!m_codeZero) {
            return false;
        }
        return m_codeZero->moveToTarget(dt);
    }

    BossMove::~BossMove()
    {
        if (!m_codeZero) {
            return ;
        }
        m_codeZero->setPos(m_targetPos);
    }

}
