#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	BabyDuxVM::BabyDuxVM() :
		m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/BabyDux.json"))
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
        int32 page = static_cast<int32>(Periodic::Triangle0_1(1.2, m_time) * 3.0);
        if (page == 3) {
            page = 2;
        }
		m_texture(U"stay")(90 * page, 0, 90, 120).drawAt(m_pos, m_colorMul);
	}
}

