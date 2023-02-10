#pragma once
#include <abyss/values/Fps.hpp> 
#include <abyss/utils/Singleton/Singleton.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    class FrameRateHz : protected Singleton<FrameRateHz>
    {
    public:
        static void Set(s3d::Optional<Fps> value)
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

        void set(const s3d::Optional<Fps>& value);
        void sleep() const;

        s3d::Optional<Fps> m_value;
        s3d::Optional<s3d::Duration> m_sleepTime;
    };
}
