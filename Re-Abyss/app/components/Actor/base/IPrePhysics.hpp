#pragma once
namespace abyss::Actor
{
    /// <summary>
    /// 地形判定の前に呼ぶ
    /// </summary>
    class IPrePhysics
    {
    public:
        virtual ~IPrePhysics() = default;
        virtual void onPrePhysics() = 0;
    };
}