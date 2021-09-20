#pragma once
#include <abyss/utils/Singleton/Singleton.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/System.hpp>
#include <Siv3D/Monitor.hpp>
#include <abyss/debugs/Log/Log.hpp>
namespace abyss
{
    class FrameRateHz : protected Singleton<FrameRateHz>
    {
    public:
        static void Set(s3d::Optional<double> value)
        {
            Instance()->set(value);
        }
        static void Sleep()
        {
            Instance()->sleep();
        }
    private:
        friend class Singleton<FrameRateHz>;
    private:
        FrameRateHz() = default;

        void set(const s3d::Optional<double>& value)
        {
            auto refreshRate = s3d::System::GetCurrentMonitor().refreshRate;
            if (value && refreshRate && *refreshRate > *value && *value > 0) {
                m_sleepTime = s3d::Duration(1.0 / (*value));
            } else {
                m_sleepTime = s3d::none;
            }
        }
        void sleep() const
        {
            if (m_sleepTime) {
                s3d::System::Sleep(*m_sleepTime);
            }
        }

        s3d::Optional<s3d::Duration> m_sleepTime;
    };
}