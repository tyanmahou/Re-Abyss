#include <abyss/views/Actor/Enemy/KingDux/BabyDux/BabyDuxVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/util/Anim/AnimUtil.hpp>
#include <Siv3D.hpp>

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
        int32 page = AnimUtil::FrameFromTriangle(1.2, m_time, 3);
        m_texture(U"stay")(90 * page, 0, 90, 100).drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawCharge() const
    {
        constexpr int32 mapping[] = { 0, 1, 2, 3, 4, 4, 5, 5, 3, 3, 3, 3 };
        int32 page = AnimUtil::FrameFromMap(m_animTime, mapping);

        m_texture(U"charge")(90 * (page % 3), 100 * (page / 3), 90, 100).drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawJump() const
    {
        constexpr int32 mapping[] = { 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int32 page = AnimUtil::FrameFromMap(m_animTime, mapping);

        m_texture(U"charge")(90 * (page % 3), 100 * (page / 3), 90, 100).drawAt(m_pos, m_colorMul);
    }
}

