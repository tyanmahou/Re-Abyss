#include <abyss/views/Actor/Enemy/CaptainTako/CpatainTakoVM.hpp>

#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    CaptainTakoVM::CaptainTakoVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/CaptainTako/CaptainTako.png"))
    {}

    CaptainTakoVM& CaptainTakoVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }

    CaptainTakoVM& CaptainTakoVM::setForward(const Forward& forward)
    {
        m_forward = forward;
        return *this;
    }
    CaptainTakoVM& CaptainTakoVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    CaptainTakoVM& CaptainTakoVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    void CaptainTakoVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            this->drawWait();
            break;
        case Motion::Charge:
            this->drawCharge();
            break;
        default:
            break;
        }
    }

    void CaptainTakoVM::drawWait() const
    {
        bool isRight = m_forward.isRight();
        int32 page = static_cast<int32>(Periodic::Triangle0_1(Param::View::AnimeTimeSec, m_time) * 3.0);
        auto tex = m_texture(40 * page, 0, 40, 40);
        tex.mirrored(isRight).draw(Arg::bottomCenter = m_pos, m_colorMul);
    }
    void CaptainTakoVM::drawCharge() const
    {
        ColorF color = ColorF(1, 1 - m_chargeRate * 0.5, 1 - m_chargeRate * 0.5) * m_colorMul;
        bool isRight = m_forward.isRight();
        int32 page = static_cast<int32>(Periodic::Triangle0_1(Param::View::AnimeTimeSec, m_time) * 3.0);

        constexpr Vec2 rawSize{40, 40};
        auto tex = m_texture({ 40 * page, 40 }, rawSize);
        const double scale = 1.0 + (m_chargeRate * Param::View::ChargingAddScale);
        const Vec2 size = s3d::Round(rawSize * scale);
        tex.mirrored(isRight).resized(size).draw(Arg::bottomCenter = m_pos, color);
    }
}
