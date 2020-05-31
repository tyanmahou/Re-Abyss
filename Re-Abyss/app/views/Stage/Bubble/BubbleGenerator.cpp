#include "BubbleGenerator.hpp"
#include <abyss/views/Stage/Bubble/BubbleEffect.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
	BubbleGenerator::BubbleGenerator():
		m_effect(WorldTime::TimeMicroSec),
		m_timer(3s, true, WorldTime::TimeMicroSec)
	{
	}

	void BubbleGenerator::draw(const s3d::Vec2& pos) const
	{
		if (m_timer.update()) {
			m_effect.add<BubbleEffect>(pos);
			m_effect.add<BubbleEffect>(pos, BubbleEffect::Small{});
			m_effect.add<BubbleEffect>(pos, BubbleEffect::Small{});
			m_effect.add<BubbleEffect>(pos, BubbleEffect::Small{});
		}

		ScopedRenderStates2D state(BlendState::Additive);
		m_effect.update();
	}

}