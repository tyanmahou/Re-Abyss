#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor
{
    class Foot : public IComponent
    {
    public:
        enum State : s3d::uint8
        {
            None = 0x0,
            Landing = 0x1,
            Ladder = 0x2,
            LadderTop = 0x6,
            Downable = 0x8,
        };
        struct LadderInfo
        {
            s3d::Vec2 pos;
        };
    private:
        State m_state = None;
        s3d::Optional<LadderInfo> m_ladderInfo;
    public:
        void reset();
        bool isNone() const;
        bool isLanding() const;
        bool isFloat() const;
        bool isLadder() const;
        bool isLadderTop() const;
        bool isDownable() const;

        Foot& updateLadderInfo(const LadderInfo& info);
        const s3d::Optional<LadderInfo>& getLadderInfo()const;

        Foot& apply(State state);

        Foot& operator |=(State state);

    };
}