#pragma once

namespace abyss::Loading
{
    class ILoading
    {
    public:
        virtual ~ILoading() = default;

        virtual bool update(double progress) = 0;
        virtual void draw() const = 0;
    };
}
