#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/WaitState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/ShotProxy.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Builder.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void WaitState::start()
    {
        using namespace Effect::Actor::Enemy::CodeZero;
        m_pActor
            ->getModule<Effects>()
            ->createWorldFront<ShotCharge::Builder>(m_body->getPos());

        m_quake = m_pActor
            ->getModule<Camera>()
            ->startQuake(1.0);
    }

    void WaitState::end()
    {
        if (m_quake) {
            m_quake->stop();
        }
    }
    Fiber<> WaitState::task()
    {
        auto shot = m_pActor->find<ShotProxy>();

        // きゅ～～ん
        shot->setIsCharge(true);
        m_scale->setTo(0.2, ShotParam::Wait::ScaleTime);
        co_await BehaviorUtil::WaitForSeconds(m_pActor, ShotParam::Wait::ScaleTime + 0.2);

        // しゅっ
        m_scale->setTo(0, 0.3);
        shot->setIsCharge(false);
        if (m_quake) {
            m_quake->stop();
        }

        // ちょっとまってから
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 1);

        // どん！
        m_scale->setTo(1.0, 0.1);
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.1);

        // ちょっとまってから
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.5);

        // 追従開始
        this->changeState<PursuitState>();
    }
    void WaitState::update()
    {
        auto dt = m_pActor->deltaTime();
        m_scale->update(dt);
    }
}

