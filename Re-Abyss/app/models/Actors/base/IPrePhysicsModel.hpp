#pragma once
namespace abyss
{
    /// <summary>
    /// 地形判定の前に呼ぶ
    /// </summary>
    class IPrePhysicsModel
    {
    public:
        virtual ~IPrePhysicsModel() = default;
        virtual void onPrePhysics() = 0;
    };
}