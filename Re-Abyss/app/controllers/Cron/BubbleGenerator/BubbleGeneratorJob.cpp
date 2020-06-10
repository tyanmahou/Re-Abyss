#include "BubbleGeneratorJob.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/views/Stage/Bubble/BubbleEffect.hpp>

namespace abyss::cron::BubbleGenerator
{
    void BubbleGeneratorJob::onExecute()
    {
		auto camera = m_pManager->getModule<Camera>();
		auto pos = camera->getPos();
		auto effects = m_pManager->getModule<Effects>();

		effects->add<EffectGroup::DecorBack, BubbleEffect>(m_pManager, pos, BubbleEffect::Big{});

		effects->add<EffectGroup::Bubble, BubbleEffect>(m_pManager, pos);
		for ([[maybe_unused]] auto&& index : step(3)) {
			effects->add<EffectGroup::Bubble, BubbleEffect>(m_pManager, pos, BubbleEffect::Small{});
		}
    }
}

