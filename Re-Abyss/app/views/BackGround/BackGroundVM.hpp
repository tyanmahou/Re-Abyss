#pragma once
#include<Siv3D/Vector2D.hpp>
#include<Siv3D/Texture.hpp>

namespace abyss
{
	class BackGroundVM
	{
		s3d::Texture m_texture;
		s3d::Vec2 m_offset;

		s3d::Vector2D<bool> m_loop;
		s3d::Vec2 m_rate;
	public:
		BackGroundVM(
			const s3d::String& path,
			const s3d::Vec2& offset,
			const s3d::Vector2D<bool>& loop,
			const s3d::Vec2& rate
		);

		void draw(const s3d::Vec2& pos)const;
	};
}