#include "BubbleGenerator.hpp"
#include <abyss/views/Stage/Bubble/BubbleEffect.hpp>
#include <abyss/controllers/TimeController/TimeController.hpp>

namespace abyss
{
	BubbleGenerator::BubbleGenerator()
	{
	}

	void BubbleGenerator::init(TimeController* pTime)
	{
		m_pTime = pTime;

		auto time = [pTime] {return pTime->timeMicroSec(); };
		m_effect = EffectEx(time);
		m_timer = IntervalTimer(3s, true, time);
	}

	void BubbleGenerator::draw(const s3d::Vec2& pos) const
	{
		if (m_timer.update()) {
			m_effect.add<BubbleEffect>(m_pTime, pos);
			m_effect.add<BubbleEffect>(m_pTime, pos, BubbleEffect::Small{});
			m_effect.add<BubbleEffect>(m_pTime, pos, BubbleEffect::Small{});
			m_effect.add<BubbleEffect>(m_pTime, pos, BubbleEffect::Small{});
		}

		ScopedRenderStates2D state(BlendState::Additive);
		m_effect.update();
	}

}