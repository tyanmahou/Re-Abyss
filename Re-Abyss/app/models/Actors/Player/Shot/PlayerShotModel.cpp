#include "PlayerShotModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace
{
    using namespace abyss;

    PlayerShotType ChargeToType(double charge)
    {
        using namespace Constants::Player;
        using enum PlayerShotType;

        if (charge >= BigCharge) {
            return Big;
        } else if (charge >= MediumCharge) {
            return Medium;
        } else if (charge >= SmallCharge) {
            return Small;
        } else {
            return Normal;
        }
    }

    double TypeToRadius(PlayerShotType type)
    {
        using enum PlayerShotType;
        static const std::unordered_map<PlayerShotType, double> rMap{
            {Normal, 5},
            {Small, 8},
            {Medium, 16},
            {Big, 24},
        };
        return rMap.at(type);
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
        using enum PlayerShotType;
        static const std::unordered_map<PlayerShotType, s3d::int32> powerMap{
            {Normal, 2},
            {Small, 3},
            {Medium, 6},
            {Big, 12},
        };
        return powerMap.at(type);
    }
}
namespace abyss
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
