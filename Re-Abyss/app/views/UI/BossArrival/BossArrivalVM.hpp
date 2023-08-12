#pragma once

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        BossArrivalVM& setPos(const s3d::Vec2& pos);
        void draw() const;
    private:
        s3d::Vec2 m_pos;
    };
}
