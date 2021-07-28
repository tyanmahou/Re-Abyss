#pragma once

namespace abyss::UI
{
    class IPostUpdate
    {
    public:
        virtual ~IPostUpdate() = default;
        virtual void onPostUpdate() = 0;
    };
}