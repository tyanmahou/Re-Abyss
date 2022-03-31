#include <abyss/views/Actor/Enemy/CodeZero/Head/EyeVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
	EyeVM::EyeVM() :
		m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CodeZero/CodeZero.json"))
	{
	}
	EyeVM& EyeVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = s3d::Round(pos);
		return *this;
	}
	EyeVM& EyeVM::setScale(double scale)
	{
		m_scale = scale;
		return *this;
	}
	EyeVM& EyeVM::setColorMul(const s3d::ColorF color)
	{
		m_colorMul = color;
		return *this;
	}
	EyeVM& EyeVM::setColorAdd(const s3d::ColorF color)
	{
		m_colorAdd = color;
		return *this;
	}
	void EyeVM::draw() const
	{
		s3d::ScopedColorAdd2D addColor(m_colorAdd);
		m_texture(U"eye").scaled(m_scale).drawAt(m_pos, m_colorMul);
	}
}
