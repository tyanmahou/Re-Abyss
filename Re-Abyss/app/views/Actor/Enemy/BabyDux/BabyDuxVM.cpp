#include <abyss/views/Actor/Enemy/BabyDux/BabyDuxVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/BabyDux/Param.hpp>
#include <abyss/views/util/Anim/AnimUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	BabyDuxVM::BabyDuxVM() :
		m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/BabyDux/BabyDux.json"))
	{}
	BabyDuxVM& BabyDuxVM::setPos(const s3d::Vec2& pos)
	{
		m_pos = s3d::Round(pos);
		return *this;
	}
    BabyDuxVM& BabyDuxVM::setEyePos(const s3d::Vec2& posL, const s3d::Vec2& posR)
    {
        m_eyePosL = posL;
        m_eyePosR = posR;
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
        this->drawEye();
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
        m_texture(U"stay")(90 * page, 0, 90, 100)
            .mirrored(m_forward.isRight())
            .drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawCharge() const
    {
        constexpr int32 mapping[] = { 0, 1, 2, 3, 4, 4, 5, 5, 3, 3, 3, 3 };
        int32 page = AnimUtil::FrameFromMap(m_animTime, mapping);

        m_texture(U"charge")(90 * (page % 3), 100 * (page / 3), 90, 100)
            .mirrored(m_forward.isRight())
            .drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawJump() const
    {
        constexpr int32 mapping[] = { 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int32 page = AnimUtil::FrameFromMap(m_animTime, mapping);

        m_texture(U"charge")(90 * (page % 3), 100 * (page / 3), 90, 100)
            .mirrored(m_forward.isRight())
            .drawAt(m_pos, m_colorMul);
    }
    void BabyDuxVM::drawEye() const
    {
        // 左目
        {
            auto eyePos = m_pos + Param::Base::EyeL * -m_forward.toVec2();
            Circle(eyePos, 8).draw();
            Circle(eyePos + m_eyePosL, 5).draw(Palette::Black);
        }

        // 右目
        {
            auto eyePos = m_pos + Param::Base::EyeR * -m_forward.toVec2();
            Circle(eyePos, 8).draw();
            Circle(eyePos + m_eyePosR, 5).draw(Palette::Black);
        }
    }
}

