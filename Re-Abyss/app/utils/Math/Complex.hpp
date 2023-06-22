#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/Math/InterpUtil.hpp>

namespace abyss
{
    struct Complex
    {
    public:
        double real;
        double imag;
    public:
        constexpr static Complex Rotate(double angle)
        {
            // if consteval
            if constexpr (std::is_constant_evaluated()) {
                auto sc = s3d::FastMath::SinCos(angle);
                return { static_cast<double>(sc.second),static_cast<double>(sc.first) };
            } else {
                return { s3d::Cos(angle), s3d::Sin(angle) };
            }
        }
        constexpr static Complex RotateDeg(double degree)
        {
            return Rotate(s3d::ToRadians(degree));
        }
        constexpr static Complex Polar(double r, double theta)
        {
            return Rotate(theta) * r;
        }
    public:
        Complex() = default;
        constexpr Complex(double _real = 0.0, double _imag = 0.0):
            real(_real),
            imag(_imag)
        {}

        constexpr Complex conjugate() const
        {
            return { real, -imag };
        }
        constexpr Complex inverse() const
        {
            double divisor = real * real + imag * imag;
            double r = real / divisor;
            double i = -imag / divisor;
            return { r, i };
        }
        constexpr double absSq() const
        {
            return real * real + imag * imag;
        }
        constexpr double abs() const
        {
            return s3d::Sqrt(absSq());
        }
        Complex normalized() const
        {
            double mag = abs();
            return { real / mag, imag / mag };
        }

        double angle() const
        {
            return s3d::Atan2(imag, real);
        }

        constexpr Complex lerp(const Complex& other, double t) const
        {
            return { real * (1 - t) + other.real * t, imag * (1 - t) + other.imag * t };
        }
        Complex slerp(const Complex& other, double t) const
        {
            auto v = InterpUtil::Slerp<double>({real, imag}, {other.real, other.imag}, t);
            return { v.x, v.y };
        }
        constexpr double dot(const Complex& other) const
        {
            return real * other.real + imag * other.imag;
        }
        constexpr Complex operator+() const
        {
            return *this;
        }
        constexpr Complex operator-() const
        {
            return { -real, -imag };
        }
        constexpr Complex operator+(const Complex& other) const
        {
            return { real + other.real, imag + other.imag };
        }
        constexpr Complex operator-(const Complex& other) const
        {
            return { real - other.real, imag - other.imag };
        }
        constexpr Complex operator*(const Complex& other) const
        {
            double r = real * other.real - imag * other.imag;
            double i = real * other.imag + imag * other.real;
            return { r, i };
        }
        constexpr Complex operator/(const Complex& other) const {
            double divisor = other.real * other.real + other.imag * other.imag;
            double r = (real * other.real + imag * other.imag) / divisor;
            double i = (imag * other.real - real * other.imag) / divisor;
            return { r, i };
        }
        constexpr Complex operator*(double s) const
        {
            return { real * s, imag * s };
        }
        friend constexpr Complex operator*(double s, const Complex& c)
        {
            return c * s;
        }
        constexpr Complex operator/(double s) const
        {
            return { real / s, imag / s };
        }

        constexpr friend s3d::Vec2 operator*(const s3d::Vec2& v, const Complex& c)
        {
            auto complex = Complex(v.x, v.y) * c;
            return { complex.real, complex.imag };
        }
    };
}
