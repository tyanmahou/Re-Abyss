#include "PlayerShot.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Actor::Player;
    using namespace abyss::Actor::Player::Shot;

    PlayerShotType ChargeToType(double charge)
    {
        if (charge >= ShotParam::Big::Charge) {
            return PlayerShotType::Big;
        } else if (charge >= ShotParam::Medium::Charge) {
            return PlayerShotType::Medium;
        } else if (charge >= ShotParam::Small::Charge) {
            return PlayerShotType::Small;
        } else {
            return PlayerShotType::Normal;
        }
    }

    double TypeToRadius(PlayerShotType type)
    {
        switch (type) {
        case PlayerShotType::Normal: return ShotParam::Normal::Radius;
        case PlayerShotType::Small: return ShotParam::Small::Radius;
        case PlayerShotType::Medium: return ShotParam::Medium::Radius;
        case PlayerShotType::Big: return ShotParam::Big::Radius;
        }
        return 0.0;
    }

    Color TypeToColor(PlayerShotType type)
    {
        using enum PlayerShotType;
        static const std::unordered_map<PlayerShotType, Color> colorMap{
            {Normal, ColorDef::Shot::NormalCharge},
            {Small, ColorDef::Shot::NormalCharge},
            {Medium, ColorDef::Shot::MediumCharge},
            {Big, ColorDef::Shot::BigCharge},
        };
        return colorMap.at(type);
    }

    s3d::int32 TypeToPower(PlayerShotType type)
    {
        switch (type) {
        case PlayerShotType::Normal: return ShotParam::Normal::Power;
        case PlayerShotType::Small: return ShotParam::Small::Power;
        case PlayerShotType::Medium: return ShotParam::Medium::Power;
        case PlayerShotType::Big: return ShotParam::Big::Power;
        }
        return 1;
    }
}
namespace abyss::Actor::Player::Shot
{
    PlayerShot::PlayerShot(double charge):
        m_type(::ChargeToType(charge))
    {}
    s3d::int32 PlayerShot::toPower() const
    {
        return ::TypeToPower(m_type);
    }
    double PlayerShot::toRadius() const
    {
        return ::TypeToRadius(m_type);
    }

    s3d::ColorF PlayerShot::toColorF() const
    {
        return ::TypeToColor(m_type);
    }
    bool PlayerShot::operator>(const PlayerShotType& type)
    {
        return static_cast<uint8>(this->m_type) > static_cast<uint8>(type);
    }
    bool PlayerShot::operator>=(const PlayerShotType& type)
    {
        return static_cast<uint8>(this->m_type) >= static_cast<uint8>(type);
    }
    bool PlayerShot::isNormal() const
    {
        return m_type == PlayerShotType::Normal;
    }
    bool PlayerShot::isSmall() const
    {
        return m_type == PlayerShotType::Small;
    }
    bool PlayerShot::isMedium() const
    {
        return m_type == PlayerShotType::Medium;
    }
    bool PlayerShot::isBig() const
    {
        return m_type == PlayerShotType::Big;
    }
}
