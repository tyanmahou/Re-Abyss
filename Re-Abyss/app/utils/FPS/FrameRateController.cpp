#include <abyss/utils/FPS/FrameRateController.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    void FrameRateController::set(const s3d::Optional<Fps>& value)
    {
        m_value = value;
        if (value) {
            m_sleepTime = s3d::DurationCast<Clock::duration>(value->duration());
            s3d::Graphics::SetVSyncEnabled(false);
        } else {
            s3d::Graphics::SetVSyncEnabled(true);
        }
    }
    bool FrameRateController::setIfLessThanRefreshRate(const s3d::Optional<Fps>& value)
    {
        auto refreshRate = s3d::System::GetCurrentMonitor().refreshRate.map([](double x) {
            return Fps{ x };
        });
        if (value && refreshRate && *value > *refreshRate) {
            // モニタのリフレッシュレートを越える
            m_value = s3d::none;
            s3d::Graphics::SetVSyncEnabled(true);
            return false;
        } else {
            this->set(value);
            return true;
        }
    }
    void FrameRateController::postPresent()
    {
        if (!m_value) {
            // 可変フレームレート
            return;
        }
        m_sleepUntil += m_sleepTime;
        m_sleepUntil = Max(m_sleepUntil,  Clock::now() - m_sleepTime);
        std::this_thread::sleep_until(m_sleepUntil);
    }
}
