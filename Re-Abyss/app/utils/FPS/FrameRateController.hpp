#pragma once
#include <abyss/utils/Singleton/AddonSingleton.hpp>
#include <abyss/values/Fps.hpp>

namespace abyss
{
    /// <summary>
    /// フレームレート制御
    /// </summary>
    class FrameRateController :
        public AddonSingleton<FrameRateController>,
        public s3d::IAddon
    {
        friend class AddonSingleton<FrameRateController>;
    private:
        using Clock = std::chrono::steady_clock;
        using TimePoint = std::chrono::time_point<Clock>;
    public:
        /// <summary>
        /// フレームレートのセット
        /// noneの場合は垂直同期
        /// </summary>
        /// <param name="value"></param>
        static void Set(const s3d::Optional<Fps>& value)
        {
            Instance()->set(value);
        }
        /// <summary>
        /// リフレッシュレート以下の場合はフレームレートのセット
        /// そうでない場合、もしくはnoneなら垂直同期
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        static bool SetIfLessThanRefreshRate(const s3d::Optional<Fps>& value)
        {
            return Instance()->setIfLessThanRefreshRate(value);
        }
    protected:
        void set(const s3d::Optional<Fps>& value);
        bool setIfLessThanRefreshRate(const s3d::Optional<Fps>& value);

        void postPresent() override;
    private:
        FrameRateController() = default;
    private:
        s3d::Optional<Fps> m_value;

        Clock::duration m_sleepTime{};
        TimePoint m_sleepUntil;
    };
}
