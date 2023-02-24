#include <abyss/components/Actor/Enemy/KingDux/State/DeadState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Adv/Adventures.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/components/Actor/Enemy/MidBossDeadCtrl.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>
#include <abyss/components/Adv/Common/EventCtrl.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void DeadState::Change(ActorObj* pActor)
	{
		pActor->find<StateCtrl>()->changeState<DeadState, StatePriority::Dead>();
	}
	void DeadState::start()
	{
		m_motion->set(Motion::Dead)
			.setAnimeTime(0);

		// 画面フラッシュ
		m_pActor->getModule<SpecialEffects>()->flush()->start(0, 0.5);

		// 当たりむこう
		m_pActor->find<ColCtrl>()->setActive(false);
		m_pActor->find<TerrainProxy>()->setActive(false);

		m_modelUpdater->setTimeScale(0);
	}
	void DeadState::end()
	{
	}
	Coro::Fiber<> DeadState::task()
	{
        if (auto signalCtrl = m_pActor->getModule<Adventures>()->find<Adv::RoomGarder::SignalCtrl>()) {
            co_await this->onDemo(signalCtrl);
        } else {
            co_await this->commonDead();
        }

        co_return;
	}
	void DeadState::update()
	{
		m_timer.update(m_pActor->deltaTime());
		switch (m_phase) {
		case Phase::Wait:
			break;
		case Phase::Explosion:
			m_motion->setAnimeTime(m_timer.rate());
			break;
		default:
			break;
		}
	}
    Fiber<> DeadState::onDemo(Ref<Adv::RoomGarder::SignalCtrl> signalCtrl)
    {
        signalCtrl->requestBattleEnd();
        co_await this->commonDead();

        signalCtrl->requestDeadEnd();

        // 死亡通知
        m_pActor->find<MidBossDeadCtrl>()->notifyDead();
        if (auto eventCtrl = signalCtrl->getObj()->find<Adv::EventCtrl>()) {
            eventCtrl->requestComplete();
        }
    }
    Fiber<> DeadState::commonDead()
    {
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);

        m_phase = Phase::Explosion;
        m_timer.reset(3.0);
        // 爆発
        {
            auto region = m_body->region().stretched(100, 0);

            for (int32 count : step(20)) {
                if (count == 4 || count == 5 || count == 11 || count == 12) {
                    // 画面フラッシュ
                    m_pActor->getModule<SpecialEffects>()->flush()->start(0.1);
                }
                auto effectPos = s3d::RandomVec2(region);
                m_pActor->getModule<Effects>()->createWorldFront<Effect::Actor::EnemyDead::Builder>(effectPos);
                m_audioSource->playAt(U"Damage", effectPos);

                co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.2);
            }
        }
        m_pActor->destroy();
    }
}
