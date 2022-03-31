#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Effect::Actor
{
	class KiranVM
	{
	public:
		KiranVM();
		KiranVM& setPos(const s3d::Vec2& pos);
		KiranVM& setScale(double sx, double sy);
		KiranVM& setRotate(double angle);

		KiranVM& setCircleRadius(double radius);

		KiranVM& setColorMul(const s3d::ColorF& color);

		void draw() const;
	private:
		TexturePacker m_texture;
		s3d::Vec2 m_pos{ 0, 0 };
		s3d::Vec2 m_scale{ 1, 1 };
		double m_angle = 0;
		double m_circleRadius = 10;

		s3d::ColorF m_colorMul;
	};
}