#pragma once

#include <Siv3D/Effect.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
	class BubbleGenerator
	{
		s3d::Effect m_effect;
		s3d::Vec2 m_pos;
	public:
		BubbleGenerator();
		void setPos(s3d::Vec2& pos);
		void update();
		void draw()const;
	};
}