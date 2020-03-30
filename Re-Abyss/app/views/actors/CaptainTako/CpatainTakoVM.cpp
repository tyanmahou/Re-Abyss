#include "CpatainTakoVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    CaptainTakoVM::CaptainTakoVM() :
        m_texture(U"resources/images/actors/CaptainTako/captain_tako.png")
    {}

    CaptainTakoVM& CaptainTakoVM::setForward(const Forward& forward)
    {
        m_forward = forward;
        return *this;
    }
    CaptainTakoVM& CaptainTakoVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Ceil(pos);
        return *this;
    }
    CaptainTakoVM& CaptainTakoVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void CaptainTakoVM::drawWait() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Triangle0_1(1s, WorldTime::Time()) * 3.0);
        auto tex = m_texture(40 * page, 0, 40, 40);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void CaptainTakoVM::drawCharge(double chargeTime) const
    {
        ColorF color = ColorF(1, 1 - chargeTime, 1 - chargeTime);
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Triangle0_1(1s, WorldTime::Time()) * 3.0);

        constexpr Vec2 rawSize{40, 40};
        auto tex = m_texture({ 40 * page, 40 }, rawSize);
        const double scale = 1.0 + (chargeTime * 0.4);
        const Vec2 size = s3d::Ceil(rawSize * scale);
        const Vec2 pos = s3d::Ceil(m_pos - size / 2.0 - Vec2{0, (size.y -rawSize.y) / 2.0});
        tex.mirrored(isRight).resized(size).draw(pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time(), color));
    }
}
