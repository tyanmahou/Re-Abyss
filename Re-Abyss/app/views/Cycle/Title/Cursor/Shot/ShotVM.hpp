#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Cycle::Title::Cursor
{
    class ShotVM
    {
		s3d::Texture m_texture;
		s3d::Vec2 m_pos;
		double m_time = 0;
	public:
		ShotVM();
		ShotVM& setTime(double time);
		ShotVM& setPos(const s3d::Vec2& pos);

		void draw();
    };
}