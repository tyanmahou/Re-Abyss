#pragma once

namespace abyss::UI::Experiment
{
    class ITopic
    {
    public:
        virtual ~ITopic() = default;
        virtual void update() = 0;
        virtual void draw() const = 0;
    };
}
