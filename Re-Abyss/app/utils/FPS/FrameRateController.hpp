#pragma once
#include <abyss/utils/Singleton/AddonSingleton.hpp>
#include <abyss/values/Fps.hpp>

namespace abyss
{
    class FrameRateController :
        public AddonSingleton<FrameRateController>,
        public s3d::IAddon
    {
        friend class AddonSingleton<FrameRateController>;
    private:
        using Clock = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<Clock>;
    public:
        static void Set(const s3d::Optional<Fps>& value)
        {
            Instance()->set(value);
        }
    private:
        static s3d::StringView UniqueName()
        {
            return U"FrameRateController";
        }
    protected:
        void set(const s3d::Optional<Fps>& value);
        void postPresent() override;
    private:
        FrameRateController() = default;
    private:
        s3d::Optional<Fps> m_value;

        Clock::duration m_sleepTime;
        TimePoint m_sleepUntil;
    };
}
