#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	BabyDuxVM::BabyDuxVM() :
		m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/BabyDux.png"))
	{}
	BabyDuxVM& BabyDuxVM::setTime(double time)
	{
		m_time = time;
		return *this;
	}
	BabyDuxVM& BabyDuxVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = s3d::Round(pos);
		return *this;
	}
	BabyDuxVM& BabyDuxVM::setColorMul(const s3d::ColorF color)
	{
		m_colorMul = color;
		return *this;
	}
	void BabyDuxVM::draw() const
	{
		m_texture.drawAt(m_pos, m_colorMul);
	}
}

