#include <abyss/utils/FPS/FrameRateHz.hpp>

namespace abyss
{
    void FrameRateHz::set(const s3d::Optional<Fps>& value)
    {
        m_value = value;
        auto refreshRate = s3d::System::GetCurrentMonitor().refreshRate.map([](double x) {
            return Fps{ x };
        });
        if (value && refreshRate && *refreshRate >= *value) {
            m_sleepTime = value->duration();
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
