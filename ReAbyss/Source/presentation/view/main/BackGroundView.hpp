#pragma once
#include<Siv3D/Vector2D.hpp>
#include<Siv3D/Texture.hpp>
#include<Siv3D/Array.hpp>

namespace abyss
{
	struct BackGroundVM
	{
		s3d::Texture texture;
		s3d::Vec2 offset;

		s3d::Vector2D<bool> loop;
		s3d::Vec2 rate;

		void draw(const s3d::Vec2& pos)const;
	};

	class BackGroundView
	{
	private:
		s3d::Array<BackGroundVM> m_bgs;
	public:
		void addBackGround(const BackGroundVM& bg);
		void draw(const s3d::Vec2& pos)const;
	};
}