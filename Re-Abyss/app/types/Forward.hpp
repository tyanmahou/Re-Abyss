#pragma once
namespace abyss
{
    /// <summary>
    /// 方向
    /// </summary>
    enum class Forward
    {
        None = 0x0,
        Up = 0x1,
        Down = 0x2,
        Left = 0x4,
        Right = 0x8,
    };

    inline double operator * (const Forward& a, double b)
    {
        if (a == Forward::Left) {
            return -b;
        }
        if (a == Forward::Right) {
            return b;
        }
        if (a == Forward::Up) {
            return -b;
        }
        if (a == Forward::Down) {
            return b;
        }
        return b;
    }
    inline double operator * (double a, const Forward& b)
    {
        return b * a;
    }
}