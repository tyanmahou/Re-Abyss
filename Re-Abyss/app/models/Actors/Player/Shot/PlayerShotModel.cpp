#include "PlayerShotModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Player;
    using namespace abyss::Player::Shot;

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
namespace abyss::Player::Shot
{
    PlayerShotModel::PlayerShotModel(double charge):
        m_type(::ChargeToType(charge))
    {}
    s3d::int32 PlayerShotModel::toPower() const
    {
        return ::TypeToPower(m_type);
    }
    double PlayerShotModel::toRadius() const
    {
        return ::TypeToRadius(m_type);
    }

    s3d::ColorF PlayerShotModel::toColorF() const
    {
        return ::TypeToColor(m_type);
    }
    bool PlayerShotModel::operator>(const PlayerShotType& type)
    {
        return static_cast<uint8>(this->m_type) > static_cast<uint8>(type);
    }
    bool PlayerShotModel::operator>=(const PlayerShotType& type)
    {
        return static_cast<uint8>(this->m_type) >= static_cast<uint8>(type);
    }
    bool PlayerShotModel::isNormal() const
    {
        return m_type == PlayerShotType::Normal;
    }
    bool PlayerShotModel::isSmall() const
    {
        return m_type == PlayerShotType::Small;
    }
    bool PlayerShotModel::isMedium() const
    {
        return m_type == PlayerShotType::Medium;
    }
    bool PlayerShotModel::isBig() const
    {
        return m_type == PlayerShotType::Big;
    }
}
