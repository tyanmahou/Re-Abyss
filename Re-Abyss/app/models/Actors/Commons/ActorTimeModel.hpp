#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Time/Time.hpp>
namespace abyss
{
    class ActorTimeModel final: public IComponent
    {
        double m_totalTimeSec = 0.0;
        double m_deltaTime = 0.0;
    public:
        void update(double dt);

        s3d::Microseconds getTime() const;
        double getDeltaTime() const;
    };
}