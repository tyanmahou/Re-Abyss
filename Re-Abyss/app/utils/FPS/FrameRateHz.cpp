#include <abyss/utils/FPS/FrameRateHz.hpp>

namespace abyss
{
    void FrameRateHz::set(const s3d::Optional<double>& value)
    {
        m_value = value;
        auto refreshRate = s3d::System::GetCurrentMonitor().refreshRate;
        if (value && refreshRate && *refreshRate >= *value && *value > 0) {
            m_sleepTime = s3d::Duration(1.0 / (*value));
            s3d::Graphics::SetVSyncEnabled(false);
        } else {
            m_sleepTime = s3d::none;
            s3d::Graphics::SetVSyncEnabled(true);
        }
    }
    void FrameRateHz::sleep() const
    {
        if (m_sleepTime) {
            s3d::System::Sleep(*m_sleepTime);
        }
    }
}
