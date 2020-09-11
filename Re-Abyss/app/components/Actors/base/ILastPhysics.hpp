#pragma once
namespace abyss::Actor
{
    /// <summary>
    /// 地形判定の後に呼ぶ
    /// </summary>
    class ILastPhysics
    {
    public:
        virtual ~ILastPhysics() = default;
        virtual void onLastPhysics() = 0;
    };
}