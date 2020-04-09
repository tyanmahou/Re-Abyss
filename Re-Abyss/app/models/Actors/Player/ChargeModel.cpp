#include "ChargeModel.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/params/Actors/Player/PlayerShotParam.hpp>

namespace abyss
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

            if (m_charge >= PlayerShotParam::Big::Charge) {
                m_charge = PlayerShotParam::Big::Charge;
            }
            return false;
        }

        // チャージショット
        if (!input.pressed() && m_charge > 0) {
            return m_charge >= PlayerShotParam::Small::Charge;
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
