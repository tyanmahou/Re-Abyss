#include "CpatainTakoVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/CaptainTako/CaptainTakoParam.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss
{
    CaptainTakoVM::CaptainTakoVM() :
        m_texture(ResourceManager::Main()->loadTexture(U"actors/CaptainTako/captain_tako.png"))
    {}

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
    CaptainTakoVM& CaptainTakoVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void CaptainTakoVM::drawWait() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Triangle0_1(CaptainTakoParam::View::AnimeTimeSec, WorldTime::Time()) * 3.0);
        auto tex = m_texture(40 * page, 0, 40, 40);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void CaptainTakoVM::drawCharge(double chargeTime) const
    {
        ColorF color = ColorF(1, 1 - chargeTime, 1 - chargeTime);
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Triangle0_1(CaptainTakoParam::View::AnimeTimeSec, WorldTime::Time()) * 3.0);

        constexpr Vec2 rawSize{40, 40};
        auto tex = m_texture({ 40 * page, 40 }, rawSize);
        const double scale = 1.0 + (chargeTime * CaptainTakoParam::View::ChargingAddScale);
        const Vec2 size = s3d::Round(rawSize * scale);
        const Vec2 pos = s3d::Round(m_pos - size / 2.0 - Vec2{0, (size.y -rawSize.y) / 2.0});
        tex.mirrored(isRight).resized(size).draw(pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time(), color));
    }
}
