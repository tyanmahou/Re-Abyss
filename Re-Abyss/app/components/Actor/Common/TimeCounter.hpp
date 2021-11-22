#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Actor
{
    class TimeCounter : public IComponent
    {
        double m_totalTime = 0;
    public:
        TimeCounter() = default;
        TimeCounter(double offset);

        void setOffset(double offset);
        void update(double dt);

        double getTotalTime()const;
    };
}