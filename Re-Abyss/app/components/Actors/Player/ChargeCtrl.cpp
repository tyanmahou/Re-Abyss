#include "ChargeCtrl.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace abyss::Actor::Player
{
    ChargeModel::ChargeModel():
        m_charge(0)
    {}

    bool ChargeModel::update(double dt)
    {
        const auto& input = InputManager::Attack;

        if (input.down()) {
            // チャージなし
            return true;
        }

        // チャージ
        if (input.pressed()) {
            m_charge += 60 * dt;

            if (m_charge >= ShotParam::Big::Charge) {
                m_charge = ShotParam::Big::Charge;
            }
            return false;
        }

        // チャージショット
        if (!input.pressed() && m_charge > 0) {
            return m_charge >= ShotParam::Small::Charge;
        }

        m_charge = 0;
        return false;
    }
    double ChargeModel::pop()
    {
        double ret = m_charge;
        m_charge = 0;
        return ret;
    }
    void ChargeModel::reset()
    {
        m_charge = 0;
    }
    double ChargeModel::getCharge() const
    {
        return m_charge;
    }
}
