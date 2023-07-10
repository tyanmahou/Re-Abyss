#include <abyss/components/Actor/Enemy/CodeZero/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Adv/Adventures.hpp>
#include <abyss/modules/Adv/base/SkipCtrl.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/EyeCtrl.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Builder.hpp>
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
	}
	void AppearState::end()
	{
		m_parts->setMoveActive(true);
        auto eye = m_pActor->find<EyeCtrl>();
		eye->setVisible(false);
		eye->flush(0.0);
		m_pActor->find<HideCtrl>()->setVisible(true);
	}
	Coro::Fiber<> AppearState::updateAsync()
	{
		if (auto signalCtrl = m_pActor->getModule<Adventures>()->find<Adv::CodeZeroDemo::SignalCtrl>()) {
            co_await(Coro::WaitWhile([signalCtrl] {return signalCtrl.isValid(); }) | this->onDemo(signalCtrl));
		}
		this->changeState<WaitState>();
		co_return;
	}
	void AppearState::update()
	{
	}
	Fiber<> AppearState::onDemo(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl)
	{
        // スキップコールバック登録
        if (auto skipCtrl = signalCtrl->getObj()->find<Adv::SkipCtrl>()) {
            skipCtrl->registCallback([
                weak = this->getWeak(),
                skipFade = m_pActor->getModule<SpecialEffects>()->skipFade()
            ] {
                if (weak) {
                    skipFade->start();
                    weak->m_isSkip = true;
                }
            });
        }
        co_await(Coro::WaitWhile([this] {return !m_isSkip; }) | this->onAppear(signalCtrl));

        // スキップ後始末
        {
            auto eye = m_pActor->find<EyeCtrl>();
            eye->setVisible(false);
            eye->flush(0.0);
            m_pActor->find<HideCtrl>()->setVisible(true);
        }

        // バトル準備
        co_await this->onPrepareBattle(signalCtrl);
	}
    Fiber<> AppearState::onAppear(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl)
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
        while (signalCtrl && !signalCtrl->isRequestedPrepareBattle()) {
            co_yield{};
        }
    }
    Fiber<> AppearState::onPrepareBattle(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl)
    {
        m_parts->setMoveActive(true);
        m_wing->startAppear();

        // 翼、手の動きと合わせる
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 2.0);
        while (signalCtrl && !signalCtrl->isBattleStart()) {
            co_yield{};
        }
    }
}
