#pragma once

#include <Siv3D/Effect.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
	class BubbleGenerator
	{
		s3d::Effect m_effect;
	public:
		BubbleGenerator();

		void draw(const s3d::Vec2& pos)const;
	};
}