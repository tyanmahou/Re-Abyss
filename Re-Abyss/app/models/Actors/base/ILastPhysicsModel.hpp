#pragma once
namespace abyss
{
    /// <summary>
    /// 地形判定の後に呼ぶ
    /// </summary>
    class ILastPhysicsModel
    {
    public:
        virtual ~ILastPhysicsModel() = default;
        virtual void onLastPhysics() = 0;
    };
}