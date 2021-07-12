#pragma once

namespace abyss::Sys
{
    class ICoreSystem
    {
    public:
        virtual ~ICoreSystem() = default;
        virtual void update() = 0;
        virtual void draw() const = 0;
    };
}