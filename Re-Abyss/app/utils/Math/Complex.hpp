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
            return { s3d::Cos(angle), s3d::Sin(angle)};
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
        double angle() const
        {
            return s3d::Atan2(imag, real);
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

    inline Complex Slerp(const Complex& start, const Complex& end, double t)
    {
        double dot = start.real * end.real + start.imag * end.imag;

        // 回転角度を計算
        double theta = s3d::Acos(dot);

        // 開始点と終点が逆方向にある場合は回転角度を補正
        if (theta > s3d::Math::Pi / 2.0) {
            theta = s3d::Math::Pi - theta;
        }

        double sinTheta = s3d::Sin(theta);
        double weightStart = s3d::Sin((1.0 - t) * theta) / sinTheta;
        double weightEnd = s3d::Sin(t * theta) / sinTheta;

        Complex interpolated = start * weightStart + end * weightEnd;
        return interpolated;
    }

    inline s3d::Vec2 Slerp(const s3d::Vec2& start, const s3d::Vec2& end, double t)
    {
        Complex startComplex(start.x, start.y);
        Complex endComplex(end.x, end.y);
        Complex erp = Slerp(startComplex, endComplex, t);
        return s3d::Vec2(erp.real, erp.imag);
    }
}
