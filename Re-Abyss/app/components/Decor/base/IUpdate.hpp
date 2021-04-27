#pragma once
namespace abyss::Decor
{
    class IUpdate
    {
    public:
        virtual ~IUpdate() = default;
        virtual void onUpdate() = 0;
    };
}