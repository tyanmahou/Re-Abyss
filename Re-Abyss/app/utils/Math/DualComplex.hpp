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
        static constexpr DualComplex Translate(const s3d::Vec2& v)
        {
            return { {1.0, 0.0}, {v.x , v.y }};
        }
        static constexpr DualComplex Rotate(double angle)
        {
            return { {s3d::Cos(angle), s3d::Sin(angle)}, {0, 0} };
        }
        static constexpr DualComplex RotateDeg(double degree)
        {
            return Rotate(s3d::ToRadians(degree));
        }
    public:
        DualComplex() = default;
        constexpr DualComplex(Complex _real, Complex _dual) :
            real(_real),
            dual(_dual)
        {}

        constexpr DualComplex conjugate() const
        {
            return { real, -dual };
        }
        constexpr DualComplex inverse() const
        {
            Complex divisor = real * real.conjugate();
            Complex newReal = real.conjugate() / divisor;
            Complex newDual = -dual * real.conjugate() / divisor;
            return { newReal, newDual };
        }
        constexpr Complex translate() const
        {
            return dual * real.conjugate();
        }
        constexpr s3d::Vec2 translateVec() const
        {
            auto trans = translate();
            return { trans.real, trans.imag };
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
        constexpr s3d::Vec2 transform(const s3d::Vec2& v) const
        {
            return (v * rotate()) + translateVec();
            //DualComplex p({ point.x, point.y }, { 0.0, 0.0 });
            //DualComplex result = *this * p * this->conjugate();
            //return s3d::Vec2{ result.real.real, result.real.imag } + translateVec();
        }
    };
}
