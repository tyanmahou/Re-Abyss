#pragma once

namespace abyss
{
    class TimeCounterModel
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