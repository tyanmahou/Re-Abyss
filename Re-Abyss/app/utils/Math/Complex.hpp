#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    struct Complex
    {
    public:
        double real;
        double imag;
    public:
        static Complex Rotate(double angle)
        {
            return { std::cos(angle), std::sin(angle)};
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
            return std::sqrt(absSq());
        }
        double angle() const
        {
            return std::atan2(imag, real);
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
