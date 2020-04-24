#pragma once

namespace abyss::Player
{
    /// <summary>
    /// player attack charge
    /// </summary>
    class ChargeModel
    {
        double m_charge;

    public:
        ChargeModel();

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