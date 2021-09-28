#pragma once
#include <abyss/utils/Singleton/Singleton.hpp>
#include <Siv3D.hpp>

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

        void set(const s3d::Optional<double>& value);
        void sleep() const;

        s3d::Optional<double> m_value;
        s3d::Optional<s3d::Duration> m_sleepTime;
    };
}