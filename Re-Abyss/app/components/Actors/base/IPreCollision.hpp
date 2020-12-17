#pragma once
namespace abyss::Actor
{
    /// <summary>
    /// 衝突判定の前に呼ぶ
    /// </summary>
    class IPreCollision
    {
    public:
        virtual ~IPreCollision() = default;
        virtual void onPreCollision() = 0;
    };
}