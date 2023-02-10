#pragma once

namespace abyss
{
    /// <summary>
    /// FPS
    /// </summary>
    class Fps
    {
    public:
        constexpr explicit Fps(double fps):
            m_fps(fps)
        {
            assert(fps > 0);
        }

        [[nodiscard]] constexpr s3d::Duration duration() const
        {
            return s3d::Duration(1.0 / m_fps);
        }

        /// <summary>
        /// フレーム数
        /// </summary>
        /// <param name="dt"></param>
        /// <returns></returns>
        [[nodiscard]] constexpr double frame(double dt) const
        {
            return dt * m_fps;
        }

        [[nodiscard]] constexpr auto operator <=> (const Fps& other) const = default;
    private:
        double m_fps = 60;
    };

    constexpr inline Fps operator""_fps(unsigned long long fps)
    {
        return Fps{ static_cast<double>(fps) };
    }
    constexpr inline Fps operator""_fps(long double fps)
    {
        return Fps{ static_cast<double>(fps) };
    }
}
