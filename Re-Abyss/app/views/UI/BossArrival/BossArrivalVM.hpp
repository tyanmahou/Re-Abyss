#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        BossArrivalVM& setPos(const s3d::Vec2& pos);

        BossArrivalVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        void draw() const;
    private:
        TexturePacker m_texture;
        s3d::Vec2 m_pos;
        double m_time = 0;
    };
}
