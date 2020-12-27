#include "BossMove.hpp"

#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Demo/DemoCtrl.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    BossMove::BossMove(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void BossMove::onStart()
    {
        auto world = m_pTalk->getModule<World>();
        m_codeZeroDemo = world->find<Actor::Enemy::CodeZero::Demo::DemoCtrl>();
        m_initPos = m_codeZeroDemo->getPos();

        m_targetPos = m_initPos - s3d::Vec2{ 0, 400 };

        m_quake = m_pTalk->getModule<Camera>()->startQuake(2.0);
    }

    Coro::Task<> BossMove::onTalk()
    {
        if (!m_codeZeroDemo) {
            co_return;
        }
        auto globalTime = m_pTalk->getModule<GlobalTime>();
        // 移動
        while (m_codeZeroDemo->moveToTarget(globalTime->deltaTime())) {
            co_yield{};
        }

        if (m_quake) {
            m_quake->stop();
        }
        auto camera = m_pTalk->getModule<Camera>();
        m_lastQuake = camera->startQuake(10, 0.3);

        while (!m_lastQuake->isEnd()) {
            co_yield{};
        }
    }

    void BossMove::onEnd()
    {
        if (m_quake) {
            m_quake->stop();
        }
        if (m_lastQuake) {
            m_lastQuake->stop();
        }
        if (!m_codeZeroDemo) {
            return;
        }
        m_codeZeroDemo->setPos(m_targetPos);
    }
}
