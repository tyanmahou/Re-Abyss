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
            return { {1.0, 0.0}, {v.x / 2.0, v.y / 2.0 }};
        }
        static constexpr DualComplex Rotate(double angle)
        {
            return { {s3d::Cos(angle / 2.0), s3d::Sin(angle / 2.0)}, {0, 0} };
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
            return {real.conjugate(), dual };
        }
        constexpr double absSq() const
        {
            return real.absSq();
        }
        constexpr double abs() const
        {
            return s3d::Sqrt(absSq());
        }
        constexpr DualComplex normalized() const
        {
            return (*this) / abs();
        }
        constexpr s3d::Vec2 translate() const
        {
            auto trans = dual * real.conjugate() * 2;
            return { trans.real, trans.imag };
        }
        double angle() const
        {
            return (real * real).angle();
        }
        constexpr DualComplex lerp(const DualComplex& other, double t) const
        {
            return ((*this) + (other - (*this)) * t);
        }
        constexpr DualComplex log() const
        {
            double lenSq = real.absSq();
            return {real.log() / lenSq, real.conjugate() * dual / lenSq };
        }
        constexpr DualComplex exp() const
        {
            auto e = real.exp();
            return { e, e * dual };
        }
        constexpr DualComplex pow(double t) const
        {
            return (this->log() * t).exp();
        }
        constexpr DualComplex sclerp(const DualComplex& other, double t) const
        {
            return (other * this->conjugate()).pow(t) * (*this);
        }
        constexpr DualComplex blend(const DualComplex& other, double t) const
        {
            return lerp(other, t).normalized();
        }
        constexpr s3d::Vec2 transform(const s3d::Vec2& v) const
        {
            auto result = this->conjugate() * DualComplex { {1, 0}, { v.x, v.y } } * (*this);
            return { result.dual.real, result.dual.imag };
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
            Complex d = real.conjugate() * other.dual + dual * other.real;
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
}
