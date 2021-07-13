#include "Generator.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/views/Stage/Bubble/BubbleEffect.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Cron::BubbleGenerator
{
	Generator::Generator(Manager* pManager):
		m_pManager(pManager)
	{}
	Coro::Task<> Generator::onExecute()
    {
		auto camera = m_pManager->getModule<Camera>();
		const auto& pos = camera->getPos();
		auto effects = m_pManager->getModule<Effects>();

		effects->createDecorBack<BubbleEffect>(m_pManager, pos, BubbleEffect::Big{});

		effects->createDecorFront<BubbleEffect>(m_pManager, pos);
		for ([[maybe_unused]] auto&& index : step(3)) {
			effects->createDecorFront<BubbleEffect>(m_pManager, pos, BubbleEffect::Small{});
		}
		co_return;
    }
}

