#include "BubbleGenerator.hpp"
#include <presentation/view/effects/Bubble.hpp>
#include <application/util/ScopedState.hpp>

namespace abyss
{
	BubbleGenerator::BubbleGenerator()
	{
		m_effect.setSpeed(0.1);
	}
	void BubbleGenerator::setPos(s3d::Vec2& pos)
	{
		m_pos = pos;
	}
	void BubbleGenerator::update()
	{
		int32 f = System::FrameCount();
		if (f % 160 == 0) {
			m_effect.add<BubbleEffect>(m_pos);
		}
	}

	void BubbleGenerator::draw() const
	{
		abyss::ScopedRenderStates2D state(BlendState::Additive);
		m_effect.update();
	}

}