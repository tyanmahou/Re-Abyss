#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	BabyDuxVM::BabyDuxVM() :
		m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/BabyDux.json"))
	{}
	BabyDuxVM& BabyDuxVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = s3d::Round(pos);
		return *this;
	}
    BabyDuxVM& BabyDuxVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    BabyDuxVM& BabyDuxVM::setAnimTime(double time)
    {
        m_animTime = time;
        return *this;
    }
	BabyDuxVM& BabyDuxVM::setColorMul(const s3d::ColorF color)
	{
		m_colorMul = color;
		return *this;
	}
	void BabyDuxVM::draw() const
	{
        if (m_motion == Motion::Wait) {
            this->drawWait();
        } else if (m_motion == Motion::Charge) {
            this->drawCharge();
        } else if (m_motion == Motion::Jump) {
            this->drawJump();
        }
    }
    void BabyDuxVM::drawWait() const
    {
        int32 page = static_cast<int32>(Periodic::Triangle0_1(1.2, m_time) * 3.0);
        if (page == 3) {
            page = 2;
        }
        m_texture(U"stay")(90 * page, 0, 90, 100).drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawCharge() const
    {
        int32 page = static_cast<int32>(m_animTime * 12);
        if (page == 12) {
            page = 11;
        }
        constexpr int32 mapping[] = {0, 1, 2, 3, 4, 4, 5, 5, 3, 3, 3, 3};

        m_texture(U"charge")(90 * (mapping[page] % 3), 100 * (mapping[page] / 3), 90, 100).drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawJump() const
    {
        int32 page = static_cast<int32>(m_animTime * 21);
        if (page == 21) {
            page = 20;
        }
        constexpr int32 mapping[] = { 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        m_texture(U"charge")(90 * (mapping[page] % 3), 100 * (mapping[page] / 3), 90, 100).drawAt(m_pos, m_colorMul);
    }
}

