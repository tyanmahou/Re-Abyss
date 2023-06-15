#pragma once
#include <abyss/utils/Math/Complex.hpp>

namespace abyss
{
    struct DualComplex
    {
    public:
        Complex real;
        Complex dual;
    public:
        static DualComplex Translate(const s3d::Vec2& v)
        {
            return { {1.0, 0.0}, {v.x * 0.5, v.y * 0.5}};
        }
        static DualComplex Rotate(double angle)
        {
            return { {std::cos(angle * 0.5), std::sin(angle * 0.5)}, {0, 0} };
        }
    public:
        DualComplex() = default;
        constexpr DualComplex(Complex _real, Complex _dual) :
            real(_real),
            dual(_dual)
        {}

        const DualComplex conjugate() const
        {
            return { real, -dual };
        }
        constexpr Complex translate() const
        {
            return dual * real.conjugate() * 2.0;
        }
        constexpr Complex rotate() const
        {
            return real;
        }

        constexpr DualComplex operator+() const
        {
            return *this;
        }
        constexpr DualComplex operator-() const
        {
            return { -real, -dual };
        }
        constexpr DualComplex operator+(const DualComplex& other) const
        {
            return { real + other.real, dual + other.dual };
        }
        constexpr DualComplex operator-(const DualComplex& other) const
        {
            return { real - other.real, dual - other.dual };
        }
        constexpr DualComplex operator*(const DualComplex& other) const
        {
            Complex r = real * other.real;
            Complex d = real * other.dual + dual * other.real;
            return { r, d };
        }
        constexpr DualComplex operator/(const DualComplex& other) const
        {
            DualComplex conjugate = other.conjugate();
            DualComplex numerator = *this * conjugate;
            DualComplex denominator = other * conjugate;
            return numerator / (denominator.real);
        }
        constexpr DualComplex operator*(double s) const
        {
            return { real * s, dual * s };
        }
        constexpr DualComplex operator*(const Complex& scalar) const
        {
            return { real * scalar, dual * scalar };
        }
        constexpr DualComplex operator/(double s) const
        {
            return { real / s, dual / s };
        }
        constexpr DualComplex operator/(const Complex& scalar) const
        {
            return { real / scalar, dual / scalar };
        }
    };
    constexpr DualComplex ScLerp(const DualComplex& start, const DualComplex& end, double t)
    {
        Complex primaryInterpolated = Slerp(start.real, end.real, t);
        Complex dualInterpolated = Slerp(start.dual, end.dual, t);
        return DualComplex(primaryInterpolated, dualInterpolated);
    }
    constexpr s3d::Vec2 ScLerp(const s3d::Vec2& start, const s3d::Vec2& end, double t)
    {
        DualComplex startDualComplex(Complex(start.x, start.y), Complex{0, 0});
        DualComplex endDualComplex(Complex(end.x, end.y), Complex{0, 0});
        DualComplex interpolatedPoint = ScLerp(startDualComplex, endDualComplex, t);
        return Vec2(interpolatedPoint.real.real, interpolatedPoint.real.imag);
    }
}
