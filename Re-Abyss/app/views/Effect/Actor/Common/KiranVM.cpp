#include <abyss/views/Effect/Actor/Common/KiranVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Effect::Actor
{
	KiranVM::KiranVM():
		m_texture(Resource::Assets::Main()->load(U"Effect/Actor/Common/CommonEffects.json"))
	{}

	KiranVM& KiranVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = pos;
		return *this;
	}

	KiranVM& KiranVM::setScale(double sx, double sy)
	{
		m_scale.x = sx;
		m_scale.y = sy;
		return *this;
	}

	KiranVM& KiranVM::setRotate(double angle)
	{
		m_angle = angle;
		return *this;
	}

	KiranVM& KiranVM::setCircleRadius(double radius)
	{
		m_circleRadius = radius;
		return *this;
	}

	KiranVM& KiranVM::setColorMul(const s3d::ColorF& color)
	{
		m_colorMul = color;
		return *this;
	}

	void KiranVM::draw() const
	{
		Circle(m_pos, m_circleRadius).drawFrame(2.0, m_colorMul);
		{
			auto baseTex = m_texture(U"kiran").scaled(m_scale.x, m_scale.y);
			baseTex.rotated(m_angle).drawAt(m_pos, m_colorMul);
			baseTex.rotated(m_angle + 90_deg).drawAt(m_pos, m_colorMul);
		}
	}

}
