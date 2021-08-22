#include "Generator.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/components/Effect/Bubble/Builder.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Cron::BubbleGenerator
{
	Generator::Generator(Manager* pManager):
		m_pManager(pManager)
	{}
	Coro::Task<> Generator::onExecute()
    {
		auto time = m_pManager->getModule<GlobalTime>();
		auto timeFunc = [time] {return time->timeMicroSec(); };
		auto effects = m_pManager->getModule<Effects>();

		using Effect::Bubble::BubbleKind;
		using Effect::Bubble::LayerKind;

		if (m_isBackBig) {
			effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Back);
			effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Front);
			effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle);
		} else {
			effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Big, LayerKind::Front);
			effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Middle, LayerKind::Back);
			effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small, LayerKind::Middle);
		}
		m_isBackBig = !m_isBackBig;
		co_return;
    }
}

