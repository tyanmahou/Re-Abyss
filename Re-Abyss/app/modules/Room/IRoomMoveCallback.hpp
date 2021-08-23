#pragma once

namespace abyss::Room
{
    class IRoomMoveCallback
    {
    public:
        virtual ~IRoomMoveCallback() = default;
        virtual void onCheckOut() = 0;
        virtual void onCheckIn() = 0;
    };
}