#pragma once

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        void draw() const;
    private:
        s3d::Vec2 m_pos;
    };
}
