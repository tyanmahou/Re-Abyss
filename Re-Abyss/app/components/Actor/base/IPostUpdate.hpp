#pragma once

namespace abyss::Actor
{
    /// <summary>
    /// Updateのあとに呼ばれる
    /// </summary>
    class IPostUpdate
    {
    public:
        virtual ~IPostUpdate() = default;
        virtual void onPostUpdate() = 0;
    };
}