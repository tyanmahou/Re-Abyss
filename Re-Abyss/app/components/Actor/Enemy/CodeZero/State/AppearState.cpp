#include <abyss/components/Actor/Enemy/CodeZero/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Novel/Novels.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/EyeCtrl.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Builder.hpp>
#include <abyss/components/Novel/Common/SkipCtrl.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	void AppearState::start()
	{
		m_head->setActive(false);
		m_parts->setMoveActive(false);

		m_pActor->find<EyeCtrl>()->setVisible(false);
		m_pActor->find<HideCtrl>()->setVisible(false);

        m_wing->startAppear();
	}
	void AppearState::end()
	{
		if (m_isSkip) {
			return;
		}
		m_parts->setMoveActive(true);
		m_pActor->find<EyeCtrl>()->setVisible(true);
		m_pActor->find<EyeCtrl>()->flush(0.0);
		m_pActor->find<HideCtrl>()->setVisible(true);
	}
	Coro::Fiber<> AppearState::task()
	{
		if (auto signalCtrl = m_pActor->getModule<Novels>()->find<Novel::CodeZeroDemo::SignalCtrl>()) {
			if (auto skipCtrl = signalCtrl->getObj()->find<Novel::SkipCtrl>()) {
				skipCtrl->registCallback([
					weak = this->getWeak(),
					skipFade = m_pActor->getModule<SpecialEffects>()->skipFade()
				]{
					if (weak) {
						skipFade->start();
						weak->end();
						weak->m_isSkip = true;
					}
				});
			}
            co_await(
                Coro::WaitWhile([signalCtrl, this] {return !m_isSkip && signalCtrl.isValid(); })
                | this->onEvent(signalCtrl)
                );
		}
		this->changeState<WaitState>();
		co_return;
	}
	void AppearState::update()
	{
	}
	Fiber<> AppearState::onEvent(Ref<Novel::CodeZeroDemo::SignalCtrl> signalCtrl)
	{
		while (signalCtrl && !signalCtrl->isRequestedAppear()) {
			co_yield{};
		}

		auto eyeCtrl = m_pActor->find<EyeCtrl>();
		eyeCtrl->setVisible(true, 4.0);
		while (!eyeCtrl->isAnimEnd()) {
			co_yield{};
		}
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.5);

		eyeCtrl->flush(0.5);
		// エフェクト
		{
			const auto effectPos = m_head->getPos() + Vec2{ 18, 33 };
			m_pActor->getModule<Effects>()
				->createWorldFront<Effect::Actor::Enemy::CodeZero::Kiran::Builder>(effectPos)
				->setTimeScale(2.5)
				;
		}
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.5);

		auto hideCtrl = m_pActor->find<HideCtrl>();
		hideCtrl->setVisible(true, 4.0);
		while (!hideCtrl->isAnimEnd()) {
			co_yield{};
		}

		if (signalCtrl) {
			signalCtrl->setAppearEnd();
		}
		while (signalCtrl && !signalCtrl->isBattleStart()) {
			co_yield{};
		}
	}
}
