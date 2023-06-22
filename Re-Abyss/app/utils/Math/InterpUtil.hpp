#pragma once
#include <abyss/values/Fps.hpp>

namespace abyss
{
    class InterpUtil
    {
    public:
        /// <summary>
        /// デルタタイムを考慮して、補間率
        /// </summary>
        static double DampRatio(double ratio, double dt, const Fps& baseFps = 60_fps);

        template <class T, class U, class V>
        static inline auto LerpDeg(const T from, const U to, const V t) noexcept
        {
            const auto diff = std::fmod(to - from, static_cast<CommonFloat_t<T, U>>(360.0));
            return (from + (std::fmod(2 * diff, static_cast<CommonFloat_t<T, U>>(360.0)) - diff) * t);
        }

        template <class T>
        static inline s3d::Vector2D<T> Slerp(const s3d::Vector2D<T>& start, const s3d::Vector2D<T>& end, double t)
        {
            auto startLen = start.length();
            auto endLen = end.length();
            if (startLen == 0 || endLen == 0) [[unlikely]] {
                return start.lerp(end, t);
            }
            auto mag = s3d::Math::Lerp(startLen, endLen, t);
            return SlerpNorm(start.normalized(), end.normalized(), t) * mag;
        }

        template <class T>
        static inline s3d::Vector2D<T> SlerpNorm(const s3d::Vector2D<T>& start, const s3d::Vector2D<T>& end, double t)
        {
            auto cos = start.dot(end);
            if (s3d::Abs(cos) > 0.9999) {
                return start.lerp(end, t);
            } else {
                auto theta = s3d::Acos(cos);
                auto sinTheta = s3d::Sin(theta);
                double scale0 = s3d::Sin((1 - t) * theta) / sinTheta;
                double scale1 = s3d::Sin(t * theta) / sinTheta;

                return start * scale0 + end * scale1;
            }
        }
        template <class T>
        static inline s3d::Vector2D<T> AngleLerpNorm(const s3d::Vector2D<T>& start, const s3d::Vector2D<T>& end, double t)
        {
            auto cos = start.dot(end);
            if (s3d::Abs(cos) > 0.9999) {
                return start.lerp(end, t);
            } else {
                auto theta = s3d::Acos(cos);
                auto sinTheta = s3d::Sin(theta);
                double scale0 = s3d::Sin((1 - t) * theta) / sinTheta;
                double scale1 = s3d::Sin(t * theta) / sinTheta;

                return start * scale0 + end * scale1;
            }
        }
        template <class T>
        static inline s3d::Vector2D<T> Nlerp(const s3d::Vector2D<T>& start, const s3d::Vector2D<T>& end, double t)
        {
            auto startLen = start.length();
            auto endLen = end.length();
            if (startLen == 0 && endLen == 0) {
                return { 0, 0 };
            } else if (startLen == 0) {
                return end;
            } else if (endLen == 0) {
                return start;
            }

            auto len = s3d::Math::Lerp(startLen, endLen, t);
            auto vec = NlerpNorm(start.normalized(), end.normalized(), t);
            return vec * len;
        }
        template <class T>
        static inline s3d::Vector2D<T> NlerpNorm(const s3d::Vector2D<T>& start, const s3d::Vector2D<T>& end, double t)
        {
            auto vec = start.lerp(end, t);
            if (!vec.isZero()) {
                vec.normalize();
            } else {
                vec = start;
            }
            return vec;
        }
    };
}
