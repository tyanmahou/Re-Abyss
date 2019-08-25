#pragma once

#include"../IView.hpp"
#include <Siv3D/Effect.hpp>

namespace abyss
{
	class BubbleGenerator :public IView
	{
		s3d::Effect m_effect;
		s3d::Vec2 m_pos;
	public:
		BubbleGenerator();
		void setPos(s3d::Vec2& pos);
		void update() override;
		void draw()const override;
	};
}