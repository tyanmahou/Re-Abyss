#pragma once

#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>
namespace abyss
{
	class BubbleGenerator
	{
		EffectEx m_effect;
		IntervalTimer m_timer;
	public:
		BubbleGenerator();

		void draw(const s3d::Vec2& pos)const;
	};
}