#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Player
{
    /// <summary>
    /// player attack charge
    /// </summary>
    class ChargeCtrl : public IComponent
    {
        double m_charge;

    public:
        ChargeCtrl();

        /// <summary>
        /// charge update
        /// </summary>
        /// <param name="dt"></param>
        /// <returns>true: attack</returns>
        bool update(double dt);

        /// <summary>
        /// return charge and charge reset
        /// </summary>
        /// <returns>charge</returns>
        double pop();

        void reset();

        double getCharge() const;
    };
}