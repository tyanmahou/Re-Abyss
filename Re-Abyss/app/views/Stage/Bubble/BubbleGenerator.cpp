#include "BubbleGenerator.hpp"
#include <abyss/views/Stage/Bubble/BubbleEffect.hpp>

namespace abyss
{
	BubbleGenerator::BubbleGenerator()
	{
		m_effect.setSpeed(0.1);
	}

	void BubbleGenerator::draw(const s3d::Vec2& pos) const
	{
		int32 f = Scene::FrameCount();
		if (f % 160 == 0) {
			m_effect.add<BubbleEffect>(pos);
			m_effect.add<BubbleEffect>(pos, BubbleEffect::Small{});
		}

		ScopedRenderStates2D state(BlendState::Additive);
		m_effect.update();
	}

}