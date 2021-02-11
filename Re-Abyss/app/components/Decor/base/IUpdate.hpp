#pragma once
namespace abyss::decor
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;
        virtual void onUpdate() = 0;
    };
}