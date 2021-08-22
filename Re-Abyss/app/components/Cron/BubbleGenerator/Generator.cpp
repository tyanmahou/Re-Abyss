#include "Generator.hpp"
#include <abyss/modules/Manager/Manager.hpp>
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
		auto effects = m_pManager->getModule<Effects>();

		using Effect::Bubble::BubbleKind;
		effects->createDecorBack<Effect::Bubble::Builder>(BubbleKind::Big);

		effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Middle);
		for ([[maybe_unused]] auto&& index : step(3)) {
			effects->createDecorFront<Effect::Bubble::Builder>(BubbleKind::Small);
		}
		co_return;
    }
}

