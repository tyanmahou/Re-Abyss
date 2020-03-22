#include "PlayerShotModel.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>

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
            {Normal, ColorF(1)},
            {Small, ColorF(1)},
            {Medium, ColorF(0.5, 0.5, 1.0)},
            {Big,  ColorF(1.0, 1.0, 0)},
        };
        return colorMap.at(type);
    }
}
namespace abyss
{
    PlayerShotModel::PlayerShotModel(double charge):
        m_type(::ChargeToType(charge))
    {}
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
