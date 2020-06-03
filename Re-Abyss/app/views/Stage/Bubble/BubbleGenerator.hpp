#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
	class BubbleGenerator
	{
		EffectEx m_effect;
		IntervalTimer m_timer;
		TimeController* m_pTime;
	public:
		BubbleGenerator();

		void init(TimeController* pTime);
		void draw(const s3d::Vec2& pos)const;
	};
}