#pragma once
#include <memory>

namespace abyss
{
    class CameraErpCtrl
    {
    public:
        void setErpRate(double rate)
        {
            m_erpRate = rate;
        }

        double rate(double dt) const;
    private:
        double m_erpRate = 1.0;
    };
}
