#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>

namespace abyss
{
    class TimeCounterModel : public IComponent
    {
        double m_totalTime = 0;
    public:
        TimeCounterModel() = default;
        TimeCounterModel(double offset);

        void setOffset(double offset);
        void update(double dt);

        double getTotalTime()const;
    };
}