#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Optional.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    class FootModel : public IComponent
    {
    public:
        enum State : s3d::uint8
        {
            None = 0x0,
            Landing = 0x1,
            Ladder = 0x2,
            LadderTop = 0x6,
        };
    private:
        State m_state = None;
        s3d::Optional<double> m_ladderPosX;
    public:
        void reset();
        bool isNone() const;
        bool isLanding() const;
        bool isFloat() const;
        bool isLadder() const;
        bool isLadderTop() const;

        FootModel& setLadderPosX(double posX);
        const s3d::Optional<double>& getLadderPosX()const;

        FootModel& apply(State state);

        FootModel& operator |=(State state);

    };
}