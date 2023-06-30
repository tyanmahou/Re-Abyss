#include <abyss/modules/Camera/CameraErp/CameraErpCtrl.hpp>
#include <abyss/utils/Math/InterpUtil.hpp>

namespace abyss
{
    double CameraErpCtrl::rate(double dt) const
    {
        if (m_erpRate >= 1 || m_erpRate <= 0) {
            return m_erpRate;
        }
        return InterpUtil::DampRatio(m_erpRate, dt, 120_fps);
    }
}
