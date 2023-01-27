#pragma once
namespace abyss::Actor
{
    /// <summary>
    /// 地形判定の後に呼ぶ
    /// </summary>
    class IPostPhysics
    {
    public:
        virtual ~IPostPhysics() = default;
        virtual void onPostPhysics() = 0;
    };
}