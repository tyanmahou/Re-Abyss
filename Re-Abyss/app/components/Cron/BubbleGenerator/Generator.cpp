#include "Generator.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Bubble/Builder.hpp>
#include <abyss/components/Effect/Bubble/Main.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Cron::BubbleGenerator
{
	Generator::Generator(Manager* pManager):
		m_pManager(pManager)
	{}
	void Generator::onStart()
	{
		s3d::Array<Ref<Effect::EffectObj>> objs;
		for (int sec = 0; sec <= 30; sec += 1) {
			if (auto effect = this->buildEffect()) {
				objs << effect;
			}
		}
		auto* pCamera = m_pManager->getModule<Camera>();
		for (size_t index = 0; index < objs.size(); ++index) {
			double sec = static_cast<double>(index) + 5.0;
			objs[index]->updateDeltaTime(sec);
			objs[index]->update();
			if (!objs[index]->find<Effect::Bubble::Main>()->isInArea(pCamera->screenRegion())) {
				// スクリーン内じゃなければ消す
				objs[index]->destroy();
			}
		}
	}
	Coro::Task<> Generator::onExecute()
    {
		auto time = m_pManager->getModule<GlobalTime>();
		auto clock = [time] {return time->timeMicroSec(); };

		this->buildEffect();
		co_yield Coro::WaitForSecondsEx(0.1s, clock);
		this->buildEffect();
		co_yield Coro::WaitForSecondsEx(0.1s, clock);
		this->buildEffect();
		co_return;
    }
	Ref<Effect::EffectObj> Generator::buildEffect()
	{
		auto effects = m_pManager->getModule<Effects>();

		using Effect::Bubble::BubbleKind;
		using Effect::Bubble::LayerKind;
		m_count = ++m_count % 6;
		switch (m_count) {
		case 0: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Front);
		case 1: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle);
		case 2: return effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Back);
		case 3: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Front);
		case 4: return effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle);
		case 5: return effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Back);
		}
		return nullptr;
	}
}

